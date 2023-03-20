/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/20 18:27:14 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	waiting(t_global *global, int size_wait)
{
	int	i;
	int	check;
	int	status;

	i = 0;
	status = 0;
	check = 0;
	while (i < size_wait)
	{
		waitpid(global->forkstates[i], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		if (status == 131 && !check++)
			ft_printf("Quit (core dumped)\n");
		i++;
	}
	signal(SIGINT, &ctrl_c);
	g_status = status;
	global->status = status;
}

int	go_exec(t_global *global)
{
	size_t	i;
	size_t	count_nb_bultin;

	i = 0;
	count_nb_bultin = 0;
	global->nb_free = global->nb - global->nb_hd;
	find_path_for_each_command(global);
	global->forkstates = malloc(sizeof(int) * global->nb);
	global->prev = -1;
	global->link[0] = -1;
	while (i < global->nb)
	{
		signal(SIGINT, SIG_IGN);
		pipe(global->link);
		forking(global, i);
		i++;
	}
	waiting(global, global->nb - count_nb_bultin);
	if (global->link[0] != -1)
		close(global->link[0]);
	free(global->forkstates);
	return (0);
}

void	ctrl_antislash(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	if (sig == SIGINT)
		exit(130);
}

int	catch_wildcards(t_global *glo, char **cmd, int idx)
{
	int	i;
	int	j;
	int	word_count;

	i = 1;
	word_count = 0;
	// fprintf(stderr, "idx >> %d\n", idx);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '*')
			{
				word_count++;
			}
			j++;
		}
		i++;
	}
	if (word_count)
	{
		activate_wc(glo, idx, word_count);
	}
	return (0);
}

int	forking(t_global *glo, unsigned long i)
{
	t_builtins	built_ptr;

	built_ptr = 0;
	if (glo->struct_id[i].split_command && glo->struct_id[i].split_command[0])
	{
		built_ptr = find_ptr_builtin(glo->struct_id[i].split_command[0]);
		if (glo->nb == 1 && built_ptr)
		{
			glo->fd_solo_redirection = dup(STDOUT_FILENO);
			if (openfiles_bt(glo, i) != -1)
				built_ptr(glo, i);
			dup2(glo->fd_solo_redirection, STDOUT_FILENO);
			close(glo->fd_solo_redirection);
			// free_inchild(glo);
			return (glo->nb--, 0);
		}
	}
	glo->forkstates[i] = fork();
	if (glo->forkstates[i] == 0)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, &ctrl_antislash);
		if (i != 0)
			dupnclose(glo->prev, STDIN_FILENO);
		if (i != (glo->nb - 1))
			dup2(glo->link[1], STDOUT_FILENO);
		close(glo->link[0]);
		close(glo->link[1]);
		if (openfiles(glo, i) == -1)
		{
			free_inchild(glo);
			exit(1);
		}
			// exit(1);
		if (glo->struct_id[i].split_command && built_ptr)
		{
			fprintf(stderr, "je suis arrive %i %s\n", __LINE__, __func__ );
			built_ptr(glo, i);
		}
		if (!glo->struct_id[i].split_command || !glo->struct_id[i].split_command[0])
		{
			if (!glo->struct_id[i].head)
				ft_printf("miniboosted: : command not found\n");
			// fprintf(stderr, "launching empty command");
			free_inchild(glo);
			exit(1);
		}
		if (ft_strchr(glo->struct_id[i].split_command[0], '/'))
			if (!access(glo->struct_id[i].split_command[0], F_OK | X_OK))
			{
				execve(glo->struct_id[i].split_command[0],
						glo->struct_id[i].split_command,
						(char **)glo->personal_env.array);
			}
		if (errno == 13)
			perror("miniboosted");
		else
			fprintf(stderr, "miniboosted: command not found : %s\n",
					glo->struct_id[i].split_command[0]);
		free_inchild(glo);
		exit(127);
	}
	else if (glo->forkstates[i] > 0)
	{
		close(glo->link[1]);
		if (glo->prev != -1)
			close(glo->prev);
		glo->prev = glo->link[0];
		if (glo->struct_id[i].prev_heredocs != -1)
			close(glo->struct_id[i].prev_heredocs);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}

void	dupnclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

t_builtins	find_ptr_builtin(char *ptr)
{
	static const t_builtins	func[7]  = {&export, &unset, &cd, &builtin_exit, &print_env, &pwd, &echo};
	static const char		*str[7] = {"export", "unset", "cd", "exit", "env", "pwd", "echo"};
	int						i;

	if (!ptr)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp(str[i], ptr))
			return (func[i]);
		i++;
	}
	return (0);
}

int	openfiles(t_global *glo, int j)
{
	t_list_mini	*list;
	int fd;

	fd = -1;
	list = glo->struct_id[j].head;
	if (!list)
		return (0);
	while (list)
	{
		if (list->redirect == OUT)
		{
			if (!*list->file_name)
			{
				ft_printf("miniboosted: ambiguous redirect\n");
				return (-1);
			}
			fd = open(list->file_name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
			if (fd == -1)
			{
				perror("miniboosted");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (list->redirect == IN)
		{
			if (!*list->file_name)
			{
				ft_printf("miniboosted: ambiguous redirect\n");
				return (-1);
			}
			fd = open(list->file_name, O_RDONLY);
			if (fd == -1)
			{
				perror("miniboosted");
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);			
		}
		else if (list->redirect == APPEND)
		{
			if (!*list->file_name)
			{
				ft_printf("miniboosted: ambiguous redirect\n");
				return (-1);
			}
			fd = open(list->file_name, O_CREAT | O_APPEND | O_WRONLY, 0666);
			if (fd == -1)
			{
				perror("miniboosted");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (list->redirect == HERE_DOC)
		{
			if (!*list->file_name)
			{
				ft_printf("miniboosted: ambiguous redirect\n");
				return (-1);
			}
			dup2(glo->struct_id[j].prev_heredocs, STDIN_FILENO);
			close(glo->struct_id[j].prev_heredocs);
		}
		list = list->next;
	}
	if (glo->nb == 1)
	{
		close(glo->link[0]);
		close(glo->link[1]);
	}
	return (0);
}

int	openfiles_bt(t_global *glo, int j)
{
	t_list_mini	*list;
	int			fd;

	list = glo->struct_id[j].head;
	while (list)
	{
		if (list->redirect == OUT)
		{
			fd = open(list->file_name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
			if (fd == -1)
			{
				perror("miniboosted");
				return (-1);
			}
			dupnclose(fd, STDOUT_FILENO); // rediriger la sortie standard
		}
		if (list->redirect == APPEND)
		{
			fd = open(list->file_name, O_CREAT | O_APPEND | O_WRONLY, 0666);
			if (fd == -1)
			{
				perror("miniboosted");
				return (-1);
			}
			dupnclose(fd, STDOUT_FILENO);
		}
		list = list->next;
	}
	close(glo->link[1]);
	return (0);
}

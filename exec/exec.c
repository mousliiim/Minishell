/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/10 04:59:18 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	waiting(t_global *global, int size_wait)
{
	int	i;
	int	exit_code;
	int	status;

	i = 0;
	status = 0;
	exit_code = 0;
	while (i < size_wait)
	{
		waitpid(global->forkstates[i], &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
		}
		i++;
	}
	global->status = exit_code;
}

int	go_exec(t_global *global)
{
	size_t	i;
	size_t	count_nb_bultin;

	i = 0;
	count_nb_bultin = 0;
	find_path_for_each_command(global);
	global->forkstates = malloc(sizeof(int) * global->nb);
	global->prev = -1;
	global->link[0] = -1;
	while (i < global->nb)
	{
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
			return (glo->nb--, 0);
		}
	}
	glo->forkstates[i] = fork();
	if (glo->forkstates[i] == 0)
	{
		if (i != 0)
			dupnclose(glo->prev, STDIN_FILENO);
		if (i != (glo->nb - 1))
			dup2(glo->link[1], STDOUT_FILENO);
		close(glo->link[0]);
		close(glo->link[1]);
		if (openfiles(glo, i) == -1)
			exit(1);
		if (glo->struct_id[i].split_command && built_ptr)
			built_ptr(glo, i);
		if (!glo->struct_id[i].split_command || !glo->struct_id[i].split_command[0])
			exit(0);
		if (!access(glo->struct_id[i].split_command[0], X_OK))
			execve(glo->struct_id[i].split_command[0],
					glo->struct_id[i].split_command,
					(char **)glo->personal_env.array);
		if (errno == 2)
			fprintf(stderr, "miniboosted: command not found : %s\n",
					glo->struct_id[i].split_command[0]);
		else
			perror("miniboosted");
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
			fd = open(list->file_name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
			if (fd == -1)
			{
				perror("miniboosted");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (list->redirect == IN)
		{
			fd = open(list->file_name, O_RDONLY);
			if (fd == -1)
			{
				perror("miniboosted");
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);			
		}
		if (list->redirect == APPEND)
		{
			fd = open(list->file_name, O_CREAT | O_APPEND | O_WRONLY, 0666);
			if (fd == -1)
			{
				perror("miniboosted");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (list->redirect == HERE_DOC)
		{
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

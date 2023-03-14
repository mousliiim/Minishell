/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/14 22:42:39 by mparisse         ###   ########.fr       */
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
	global->nb_free = global->nb;
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

int	activate_wc(t_global *glo, char *cmd, int i)
{
	DIR *dir;
	size_t	len;
	int	word_count;
	size_t	len2;
	int		j;
	char	**new_args;
	struct dirent *dent;

	// (void) cmd;
	word_count = 1;
	if (cmd[0] == '*')
	{
		dir = opendir(".");
		dent = readdir(dir);
		while (dent != NULL)
		{
			len = ft_strlen(&cmd[1]);
			len2 = ft_strlen(dent->d_name);
			if (!ft_strncmp(&cmd[1], &dent->d_name[len2 - len], len))
			{
				word_count++;
			}
			dent=readdir(dir);
		}
		closedir(dir);
		new_args = malloc(sizeof(char *) * word_count + 1);
		new_args[0] = ft_strdup(glo->struct_id[i].split_command[0]);
		dir = opendir(".");
		dent = readdir(dir);
		j = 1;
		while (dent != NULL)
		{
			len = ft_strlen(&cmd[1]);
			len2 = ft_strlen(dent->d_name);
			if (!ft_strncmp(&cmd[1], &dent->d_name[len2 - len], len))
			{
				new_args[j] = ft_strdup(dent->d_name);
				j++;
			}
			dent=readdir(dir);
		}
		closedir(dir);
		new_args[j] = 0;
		// free_double_str(glo->struct_id[i].split_command);
		glo->struct_id[i].split_command = new_args;
	}
	j = 0;
	while (glo->struct_id[i].split_command[j])
	{
		fprintf(stderr, "cmd[%d] >> %s\n", i, glo->struct_id[i].split_command[j]);
		j++;
	}
	return (0);
}

int	catch_wildcards(t_global *glo, char **cmd, int idx)
{
	int	i;
	int	j;
	// (void) glo;

	i = 1;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '*')
			{
				activate_wc(glo, cmd[i], idx);
			}
			j++;
		}
		i++;
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
			exit(1);
		if (glo->struct_id[i].split_command && built_ptr)
			built_ptr(glo, i);
		if (!glo->struct_id[i].split_command || !glo->struct_id[i].split_command[0])
			exit(0);
		// catch_wildcards(glo, glo->struct_id[i].split_command, i);
		if (ft_strchr(glo->struct_id[i].split_command[0], '/'))
			if (!access(glo->struct_id[i].split_command[0], F_OK | X_OK))
				execve(glo->struct_id[i].split_command[0],
						glo->struct_id[i].split_command,
						(char **)glo->personal_env.array);
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

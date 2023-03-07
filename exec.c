/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/07 03:05:54 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	find_path_for_each_command(t_global *global)
{
	int				i;
	int				j;
	t_tab_struct	*struc;
	char			*command_w_path;

	i = 0;
	struc = global->struct_id;
	if (!global->path)
		return (0);
	if (struc[i].split_command == NULL)
		return (0);
	while (i < global->nb)
	{
		j = 0;
		if (find_ptr_builtin(struc[i].split_command[0]))
		{
			i++;
			continue ;
		}
		while (global->path[j])
		{
			if (!struc[i].split_command[0])
				break ;
			command_w_path = ft_sup_strjoin(global->path[j], '/',
					struc[i].split_command[0]);
			if (access(command_w_path, F_OK | X_OK) != -1)
			{
				free(struc[i].split_command[0]);
				struc[i].split_command[0] = command_w_path;
				break ;
			}
			free(command_w_path);
			j++;
		}
		i++;
	}
	return (0);
}

void	dupnclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

builtins	find_ptr_builtin(char *ptr)
{
	static const builtins	func[7]  = {&export, &unset, &cd, &builtin_exit, &print_env, &pwd, &echo};
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

int	replace_by_expand(t_global *glo, char *str, int idx_command, int idx_word)
{
	int	i;
	int	stuff;

	i = 0;
	if (!str)
		return (0);
	while (glo->personal_env.array[i])
	{
		stuff = ft_strchr((char *)glo->personal_env.array[i], '=')
			- (char *)glo->personal_env.array[i];
		if (!ft_strncmp(str, (char *)glo->personal_env.array[i], stuff))
		{
			fprintf(stderr, "replace command\n");
			glo->struct_id[idx_command].split_command[idx_word] = ft_substr((char *)glo->personal_env.array[i],
					stuff + 1, 56);
			fprintf(stderr, ">> %s\n", str);
			break ;
		}
		i++;
	}
	return (0);
}

int	catch_expand(t_global *glo, int j)
{
	int	i;
	int	word_idx;

	word_idx = 0;
	while (glo->struct_id[j].split_command[word_idx])
	{
		i = 0;
		while (glo->struct_id[j].split_command[word_idx][i])
		{
			if (glo->struct_id[j].split_command[word_idx][i] == '$')
			{
				fprintf(stderr, "catch expand\n");
				replace_by_expand(glo,
						&glo->struct_id[j].split_command[word_idx][i + 1], j,
						word_idx);
				fprintf(stderr, ">> %s\n",
						&glo->struct_id[j].split_command[word_idx][i + 1]);
				break ;
			}
			i++;
		}
		word_idx++;
	}
	return (0);
}

// int get_fds(int open_way, char *file_name)
// {
// 	if (open_way == 1) 
// }
// int	start_heredoc(t_global *glo, int j)
// {
// 	int	link_heredoc[2];

// 	pipe(link_heredoc);
// 	while (1)
// 	{
// 		if ()
// 	}
// }
// finir redirections 
// quotes
// signaux ctrlc
// expand

// int	start_heredoc(t_global *glo, int j, t_list_mini *head)
// {
// 	char	*str;
// 	int		link_heredoc[2];
// 	char	*limit;

// 	limit = ft_strjoin(head->file_name, "\n");
// 	pipe(link_heredoc);
// 	// fprintf
// 	while (1)
// 	{
// 		fprintf(stderr, "start heredoc\n");
// 		// printf("here_doc:");
// 		str = readline("here_doc:");
// 		if (!ft_strcmp(str, limit))
// 		{
// 			break;
// 		}
// 		ft_putstr_fd(str, glo->link[1]);
// 		free(str);
// 	}
// 	return (0);
// }

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

int	forking(t_global *glo, int i)
{
	builtins	built_ptr;

	if (glo->struct_id->split_command)
	{
		built_ptr = find_ptr_builtin(glo->struct_id[i].split_command[0]);
		if (glo->nb == 1 && built_ptr)
			return (built_ptr(glo, i), glo->nb--, 0);
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
		if (glo->struct_id->split_command && built_ptr)
			built_ptr(glo, i);
		if (!glo->struct_id->split_command || !glo->struct_id[i].split_command[0])
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

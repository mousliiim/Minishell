/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/02 22:22:54 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_exec(t_global *global)
{
	size_t		i;
	// int			test;
	size_t		count_nb_bultin;
	// builtins	ok;

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
	waiting(global->forkstates, global->nb - count_nb_bultin);
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
	while (i < global->nb)
	{
		j = 0;
		while (global->path[j])
		{
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
	static const builtins	func[8] = {&export, &unset, &cd, &builtin_exit, &print_env, &print_env, &pwd, &pwd};
	static const char		*str[8] = {"export", "unset", "cd", "exit", "/usr/bin/env", "env", "/usr/bin/pwd", "pwd"};
	int						i;

	i = 0;
	while (i < 8)
	{
		if (!ft_strcmp(str[i], ptr))
			return (func[i]);
		i++;
	}
	return (0);
}

int	forking(t_global *glo, int i)
{
	builtins	built_ptr;

	built_ptr = find_ptr_builtin(glo->struct_id[i].split_command[0]);
	if (glo->nb == 1 && built_ptr)
		return (built_ptr(glo, i), glo->nb--, 0);
	glo->forkstates[i] = fork();
	if (glo->forkstates[i] == 0)
	{
		if (i != 0)
			dupnclose(glo->prev, STDIN_FILENO);
		if (i != (glo->nb - 1))
			dup2(glo->link[1], STDOUT_FILENO);
		close(glo->link[0]);
		close(glo->link[1]);
		if (built_ptr)
			built_ptr(glo, i);
		if (!access(glo->struct_id[i].split_command[0], X_OK))
			execve(glo->struct_id[i].split_command[0],
					glo->struct_id[i].split_command,
					(char **)glo->personal_env.array);
		if (errno == 2)
			fprintf(stderr, "miniboosted: command not found : %s\n", glo->struct_id[i].split_command[0]);
		else
			perror("miniboosted");
		exit(0);
	}
	else if (glo->forkstates[i] > 0)
	{
		close(glo->link[1]);
		if (glo->prev != -1)
			close(glo->prev);
		glo->prev = glo->link[0];
	}
	return (0);
}


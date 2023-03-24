/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/24 20:29:28 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	waiting(t_global *global, int size_wait)
{
	int	i;
	int	check;
	int	status;

	if (!global->nb)
		return ;
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

// void	free_exec_malloc(t_global *global)
// {
// 	size_t	i;

// 	i = 0;
// 	free_shell(global, NULL, 0);
// 	free_double_str(global->path);
// 	clear_lst(global->struct_id, global->nb);
// 	while (i < global->nb)
// 	{
// 		free_double_str(global->struct_id[i].split_command);
// 		free_double_str(global->struct_id[i].commands);
// 		i++;
// 	}
// 	free(global->struct_id);
// 	exit(1);
// }

int	go_exec(t_global *global)
{
	size_t	i;
	size_t	count_nb_bultin;

	i = 0;
	count_nb_bultin = 0;
	global->nb_free = global->nb - global->nb_hd;
	if (!find_path_for_each_command(global))
		free_exec_malloc(global);
	global->forkstates = malloc(sizeof(int) * global->nb);
	if (!global->forkstates)
		free_exec_malloc(global);
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

int	forking(t_global *glo, unsigned long i)
{
	t_builtins	built_ptr;

	built_ptr = 0;
	glo->fd_solo_redirection = -1;
	if (glo->struct_id[i].split_command && glo->struct_id[i].split_command[0])
	{
		built_ptr = find_ptr_builtin(glo->struct_id[i].split_command[0]);
		if (glo->nb == 1 && built_ptr)
		{
			builtin_solo_process(glo, built_ptr, i);
			return (glo->nb--, 0);
		}
	}
	glo->forkstates[i] = fork();
	if (glo->forkstates[i] == 0)
		child_process(glo, built_ptr, i);
	else if (glo->forkstates[i] > 0)
		father_process(glo, i);
	return (0);
}

void	dupnclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

t_builtins	find_ptr_builtin(char *ptr)
{
	static const t_builtins	func[7] = {&export, &unset, &cd,
		&builtin_exit, &print_env, &pwd, &echo};
	static const char		*str[7] = {"export", "unset", "cd",
		"exit", "env", "pwd", "echo"};
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

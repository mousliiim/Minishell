/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/28 02:45:40 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(t_global *global, char *added)
{
	pa_add(&global->personal_env, ft_strdup(added));
}

void	export(t_global *global, int j)
{
	if (ft_isdigit(global->struct_id[j].split_command[1][0]) == 1
		&& global->struct_id[j].split_command[1][0] == '=')
	{
		ft_printf("bash: export : '%s': not a valid identfier\n",
					global->struct_id[j].split_command[1]);
		return ;
	}
	pa_add(&global->personal_env,
			ft_strdup(global->struct_id[j].split_command[1]));
}

int	go_exec(t_global *global)
{
	size_t	i;
	size_t	count_nb_bultin;

	// builtins	tab[1];
	// tab[0] = &export;
	i = 0;
	count_nb_bultin = 0;
	find_path_for_each_command(global);
	global->forkstates = malloc(sizeof(int) * global->nb);
	// protege
	global->prev = -1;
	global->link[0] = -1;
	while (i < global->nb)
	{
		if (!ft_strcmp("export", global->struct_id[i].split_command[0]))
		{
			export(global, i);
			count_nb_bultin++;
		}
		else
		{
			pipe(global->link);
			forking(global, i);
		}
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

int	forking(t_global *glo, int i)
{
	glo->forkstates[i] = fork();
	if (glo->forkstates[i] == 0)
	{
		if (i != 0)
			dupnclose(glo->prev, STDIN_FILENO);
		if (i != (glo->nb - 1))
			dup2(glo->link[1], STDOUT_FILENO);
		// openfiles
		close(glo->link[0]);
		close(glo->link[1]);
		execve(glo->struct_id[i].split_command[0],
				glo->struct_id[i].split_command,
				(char **)glo->personal_env.array);
		exit(0);
	}
	else if (glo->forkstates[i] > 0)
	{
		close(glo->link[1]);
		if (glo->prev != -1)
			close(glo->prev);
		glo->prev = glo->link[0];
	}
	// ft_printf("-------------\n\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/26 21:44:53 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(t_global *global, char *env)
{
	int	i;

	while (global->env[i])
	{
		i++;
	}
	ft_printf("global->env[i] >> %s\n", global->env[i]);
}

void	export(t_global *global, int j)
{
	int	i;
	int start;
	
	i = 0;

	if (ft_isdigit(global->struct_id[j].split_command[1][0]) == 1 && global->struct_id[j].split_command[1][0] == '=')
	{
		ft_printf("bash: export : '%s': not a valid identfier\n", global->struct_id[j].split_command[1]);
		return ;
	}
	while (global->struct_id[j].split_command[1][i])
	{
		if (global->struct_id[j].split_command[1][i] == '=')
			start = i;
		i++;
	}
	fprintf(stderr ,">> %s\n", &global->struct_id[j].split_command[1][start]);
	add_env(global, &global->struct_id[j].split_command[1][start]);
}

int	go_exec(t_global *global)
{
	int	i;
	builtins tab[1] = {&export};

	i = 0;
	find_path_for_each_command(global);
	global->forkstates = malloc(sizeof(int) * global->nb);
	// protege 
	global->prev = -1;
	while (i < global->nb)
	{
		// printf("i >. %d\n", i);
		if (!ft_strcmp("export", global->struct_id[i].split_command[0]))
		{
			ft_printf("cette commande est export\n");
			tab[0](global, i);
			// export(global, i);
			global->nb--;
		}
		else
		{
			pipe(global->link);
			forking(global, i);
		}
		i++;
	}
	waiting(global->forkstates, global->nb);
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
	while (i < global->nb)
	{
		j = 0;
		while (global->path[j])
		{
			command_w_path = ft_sup_strjoin(global->path[j], '/', struc[i].split_command[0]);
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

int	forking(t_global *global, int i)
{
	global->forkstates[i] = fork();
	if (global->forkstates[i] == 0)
	{
		if (i == global->nb - 1)
		{
			if (global->nb != 1)
				dup2(global->prev, STDIN_FILENO);
			close(global->link[0]);
		}
		else if (i == 0)
		{
			dup2(global->link[1], STDOUT_FILENO);
			close(global->link[0]);
		}
		else if (i > 0 && i < (global->nb - 1))
		{
			dup2(global->prev, STDIN_FILENO);
			dup2(global->link[1], STDOUT_FILENO);
			close(global->link[0]);
		}
		if (global->prev != -1)
			close(global->prev);
		close(global->link[1]);
		execve(global->struct_id[i].split_command[0], global->struct_id[i].split_command, global->env);
		exit(0);
	}
	if (global->prev != -1)
		close(global->prev);
	close(global->link[1]);
	global->prev = global->link[0];
	if (i == global->nb - 1)
		close(global->link[0]);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function_sequel.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 07:54:37 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/24 19:04:39 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_exec_malloc(t_global *global)
{
	size_t	i;

	i = 0;
	free_shell(global, NULL, 0);
	free_double_str(global->path);
	clear_lst(global->struct_id, global->nb);
	while (i < global->nb)
	{
		free_double_str(global->struct_id[i].split_command);
		free_double_str(global->struct_id[i].commands);
		i++;
	}
	free(global->struct_id);
	exit(1);
}

void	free_path_malloc(t_global *global)
{
	size_t	i;

	i = 0;
	free_shell(global, NULL, 0);
	clear_lst(global->struct_id, global->nb);
	while (i < global->nb)
	{
		free_double_str(global->struct_id[i].split_command);
		free_double_str(global->struct_id[i].commands);
		i++;
	}
	free(global->struct_id);
	exit(1);
}

void	free_array(t_ptr_array pa)
{
	size_t	i;

	i = 0;
	while (i < pa.size)
	{
		free(pa.array[i]);
		i++;
	}
	free(pa.array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:00:29 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/10 02:24:06 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

t_ptr_array	build_personal_env(char **env)
{
	int			i;
	t_ptr_array	res;

	i = 0;
	res = pa_new();
	while (env[i])
	{
		pa_add(&res, ft_strdup(env[i]));
		i++;
	}
	return (res);
}

char	**set_path(t_global *global)
{
	size_t	i;
	char	**path;

	i = 0;
	if (global->personal_env.size == 0)
		return (0);
	else
	{
		while (i < global->personal_env.size)
		{
			if (ft_strnstr((char *)global->personal_env.array[i], "PATH=", 5))
			{
				path = ft_split((char *)global->personal_env.array[i] + 5, ':');
				if (!path || !*path)
					return (0);
				return (path);
			}
			i++;
		}
	}
	return (0);
}

int	find_path_for_each_command(t_global *global)
{
	size_t			i;
	size_t			j;
	t_tab_struct	*struc;
	char			*command_w_path;

	i = 0;
	struc = global->struct_id;
	if (!global->path)
		return (0);
	while (i < global->nb)
	{
		j = 0;
		if (!struc[i].split_command)
		{
			i++;
			continue ;
		}
		if (find_ptr_builtin(struc[i].split_command[0]) && struc[i].split_command)
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

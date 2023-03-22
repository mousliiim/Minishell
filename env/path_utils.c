/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:00:29 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/22 22:59:50 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

char	*getter(char *env_var)
{
	int	stop;

	stop = ft_strchr(env_var, '=') - env_var;
	return (&env_var[stop + 1]);
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

int	pa_add_env(t_ptr_array *pa, char *new_str)
{
	t_ptr_array	tmp;

	if (pa->size == pa->capacity)
	{
		pa->capacity *= 2;
		tmp = *pa;
		pa->array = ft_realloc(pa->array, pa->size, pa->capacity
				* sizeof(char *));
		if (!pa->array)
		{
			free_array(tmp);
			pa->capacity = 0;
			return (0);
		}
	}
	pa->array[pa->size++] = new_str;
	return (1);
}

t_ptr_array	build_personal_env(char **env)
{
	int			i;
	char		*tmp;
	t_ptr_array	res;

	i = 0;
	res = pa_new();
	if (!res.capacity)
		exit(1);
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_double_str((char **)res.array), res);
		if (!pa_add_env(&res, tmp))
		{
			free(tmp);
			return (res);
		}
		i++;
	}
	return (res);
}

void	free_path_malloc(t_global *global)
{
	size_t	i;

	i = 0;
	free_shell(global, NULL);
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

char	**set_path(t_global *global)
{
	size_t	i;
	char	**path;

	i = -1;
	if (global->personal_env.size == 0)
		return (0);
	else
	{
		while (++i < global->personal_env.size)
		{
			if (ft_strnstr((char *)global->personal_env.array[i], "PATH=", 5))
			{
				path = ft_split((char *)global->personal_env.array[i] + 5, ':');
				if (!path || !*path)
				{
					free_path_malloc(global);
					return (0);
				}
				return (path);
			}
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
		return (1);
	while (i < global->nb)
	{
		j = 0;
		if (!struc[i].split_command)
		{
			i++;
			continue ;
		}
		if (find_ptr_builtin(struc[i].split_command[0])
			&& struc[i].split_command)
		{
			i++;
			continue ;
		}
		while (global->path[j])
		{
			if (!struc[i].split_command[0])
				break ;
			if (ft_strchr(struc[i].split_command[0], '/'))
				break ;
			command_w_path = ft_sup_strjoin(global->path[j], '/',
					struc[i].split_command[0]); // malloc
			if (!command_w_path)
				return (0);
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
	return (1);
}

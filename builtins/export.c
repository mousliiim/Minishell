/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:53 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/27 04:42:08 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static int	ft_identifier(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	if (str[0] == '=' && !str[1])
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	i++;
	}
	return (1);
}

void	export_error_message(char *str)
{
	ft_putstr_fd("MiniBoosted: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("' : not a valid identifier\n", 2);
}

int	check_identifier(t_global *global, int j, int idx_args)
{
	int		i;
	char	*str;

	i = 0;
	str = global->struct_id[j].split_command[idx_args];
	while (global->struct_id[j].split_command[idx_args][i])
	{
		if (!ft_identifier(str))
		{
			export_error_message(global->struct_id[j].split_command[idx_args]);
			g_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_env(t_global *global, int j, int idx_args, int stuff)
{
	int	i;

	i = -1;
	while (global->personal_env.array[++i])
	{
		if (!ft_strncmp(global->struct_id[j].split_command[idx_args],
				(char *)global->personal_env.array[i],
				stuff))
			return (i);
	}
	return (-1);
}

int	export(t_global *global, int j)
{
	int	stuff;
	int	idx_args;
	int	i;

	idx_args = 0;
	g_status = 0;
	while (global->struct_id[j].split_command[++idx_args])
	{
		if (check_identifier(global, j, idx_args) == 0)
			continue ;
		stuff = ft_strchr(global->struct_id[j].split_command[idx_args], '=')
			- global->struct_id[j].split_command[idx_args];
		if (stuff > 0)
		{
			i = check_env(global, j, idx_args, stuff);
			if (i != -1)
				pa_pop(&global->personal_env, i);
			pa_add(&global->personal_env,
				ft_strdup(global->struct_id[j].split_command[idx_args]));
		}
	}
	return (0);
}

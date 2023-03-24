/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:53 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/24 19:51:05 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	check_identifier(t_global *global, int j, int idx_args)
{
	if (!global->struct_id[j].split_command[idx_args])
	{
		ft_printf("bash: export : '%s': not a valid identfier\n",
			global->struct_id[j].split_command[idx_args]);
		g_status = 1;
		return (0);
	}
	if (ft_isdigit(global->struct_id[j].split_command[idx_args][0]) == 1
		|| global->struct_id[j].split_command[idx_args][0] == '=')
	{
		ft_printf("bash: export : '%s': not a valid identfier\n",
			global->struct_id[j].split_command[idx_args]);
		g_status = 1;
		return (0);
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
				(char *)global->personal_env.array[i], stuff))
		{
			pa_pop(&global->personal_env, i);
			return (i);
		}
	}
	return (-1);
}

void	export_error_message(char *str)
{
	ft_putstr_fd("miniboosted: export:'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
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
		else
			export_error_message(global->struct_id[j].split_command[idx_args]);
	}
	return (0);
}

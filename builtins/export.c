/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:53 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/22 18:25:40 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	export(t_global *global, int j)
{
	int		stuff;
	int		idx_args;
	int		i;

	idx_args = 1;
	g_status = 0;
	while (global->struct_id[j].split_command[idx_args])
	{
		if (!global->struct_id[j].split_command[idx_args])
		{
			ft_printf("bash: export : '%s': not a valid identfier\n",
						global->struct_id[j].split_command[idx_args]);
			idx_args++;
			g_status = 1;
			continue ;
		}
		if (ft_isdigit(global->struct_id[j].split_command[idx_args][0]) == 1
			|| global->struct_id[j].split_command[idx_args][0] == '=')
		{
			ft_printf("bash: export : '%s': not a valid identfier\n",
						global->struct_id[j].split_command[idx_args]);
			idx_args++;
			g_status = 1;
			continue ;
		}
		stuff = ft_strchr(global->struct_id[j].split_command[idx_args], '=') - global->struct_id[j].split_command[idx_args];
		i = 0;
		if (stuff > 0)
		{
			while (global->personal_env.array[i])
			{
				if (!ft_strncmp(global->struct_id[j].split_command[idx_args], (char *)global->personal_env.array[i], stuff))
				{
					pa_pop(&global->personal_env, i);
					break ;
				}
				i++;
			}
			pa_add(&global->personal_env,
			ft_strdup(global->struct_id[j].split_command[idx_args]));
		}
		else
			printf("bash: export : '%s': not a valid identfier\n",
					global->struct_id[j].split_command[idx_args]);
		idx_args++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:02:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/02 05:36:03 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_global *global, int j)
{
	int	stuff;
	int	i;

	if (global->nb > 1)
		exit(0);
	if (!global->struct_id[j].split_command[1])
		return (0);
	if (ft_isdigit(global->struct_id[j].split_command[1][0]) == 1
		|| global->struct_id[j].split_command[1][0] == '=')
	{
		ft_printf("bash: export : '%s': not a valid identfier\n",
					global->struct_id[j].split_command[1]);
		return (0);
	}
	stuff = ft_strchr(global->struct_id[j].split_command[1], '=') - global->struct_id[j].split_command[1];
	i = 0;
	if (stuff > 0)
	{
		while (global->personal_env.array[i])
		{
			if (!ft_strncmp(global->struct_id[j].split_command[1], (char *)global->personal_env.array[i], stuff))
			{
				pa_pop_replace(&global->personal_env, i, global->struct_id[j].split_command[1]);
				pa_add(&global->personal_env,
						ft_strdup(global->struct_id[j].split_command[1]));
				return (0);
			}
			i++;
		}
		pa_add(&global->personal_env,
				ft_strdup(global->struct_id[j].split_command[1]));
	}
	return (0);
}

int	unset(t_global *glo, int j)
{
	int		i;
	size_t	len;

	if (glo->nb > 1)
		exit(0);
	len = ft_strlen(glo->struct_id[j].split_command[1]);
	i = 0;
	while (glo->personal_env.array[i])
	{
		if (!ft_strncmp(glo->struct_id[j].split_command[1], (char *)glo->personal_env.array[i], len))
		{
			pa_pop(&glo->personal_env, i);
			return (0);
		}
		i++;
	}
	return (0);
}

int	cd(t_global *global, int i)
{
	int	status;

	if (global->nb > 1)
		exit(0);
	status = 0;
	if (status != 0)
		perror("Error changing directory");
	status = chdir(global->struct_id[i].split_command[1]);
	return (status);
}

int	builtin_exit(t_global *global, int j)
{
	int	i;

	if (global->nb > 1)
		exit(0);
	if (!global->struct_id[j].split_command[1])
		exit(0);
	i = 0;
	while (global->struct_id[j].split_command[1][i])
	{
		if (!ft_isdigit(global->struct_id[j].split_command[1][i]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(global->struct_id[j].split_command[1], 2);
			ft_putstr_fd(": numeric argument required", 2);
			exit(0);
		}
		i++;
	}
	exit ((unsigned char )ft_atoi(global->struct_id[j].split_command[1]));
}
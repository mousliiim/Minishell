/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:02:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/02 23:09:44 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_global *global, int j)
{
	int		stuff;
	int		idx_args;
	int		i;

	if (global->nb > 1)
		exit(0);
	idx_args = 1;
	while (global->struct_id[j].split_command[idx_args])
	{
		if (!global->struct_id[j].split_command[idx_args])
		{
			ft_printf("bash: export : '%s': not a valid identfier\n",
						global->struct_id[j].split_command[idx_args]);
			idx_args++;
			continue ;
		}
		if (ft_isdigit(global->struct_id[j].split_command[idx_args][0]) == 1
			|| global->struct_id[j].split_command[idx_args][0] == '=')
		{
			ft_printf("bash: export : '%s': not a valid identfier\n",
						global->struct_id[j].split_command[idx_args]);
			idx_args++;
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
					pa_pop_replace(&global->personal_env, i, global->struct_id[j].split_command[idx_args]);
					pa_add(&global->personal_env,
							ft_strdup(global->struct_id[j].split_command[idx_args]));
					idx_args++;
					continue ;
				}
				i++;
			}
			pa_add(&global->personal_env,
					ft_strdup(global->struct_id[j].split_command[idx_args]));
		}
		idx_args++;
	}
	return (0);
}

int	unset(t_global *glo, int j)
{
	int		i;
	int		idx_args;
	size_t	len;

	if (glo->nb > 1)
		exit(0);
	idx_args = 1;
	while (glo->struct_id[j].split_command[idx_args])
	{
		len = ft_strlen(glo->struct_id[j].split_command[idx_args]);
		i = 0;
		while (glo->personal_env.array[i])
		{
			if (!ft_strncmp(glo->struct_id[j].split_command[idx_args], (char *)glo->personal_env.array[i], len))
			{
				pa_pop(&glo->personal_env, i);
				break ;
			}
			i++;
		}
		idx_args++;
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

int	print_env(t_global *glo, int j)
{
	int	i;

	(void) j;
	i = -1;
		while (glo->personal_env.array[++i])
		printf("%s\n", (char *)glo->personal_env.array[i]);
	if (glo->nb > 1)
		exit(0);
	return (0);
}

int	pwd(t_global *glo, int j)
{
	char	pwdd[4096] = {0};

	getcwd(pwdd, 4096);
	printf("%s\n", pwdd);
	if (glo->nb > 1)
		exit(0);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:53 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/26 00:40:31 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ft_identifier(int c, char *str)
{
	int	i;

	i = -1;
	if (ft_isdigit(c) || c == '\\')
	{
		while (str[++i] != '=')
		{
			if (ft_isalpha(str[i]) || str[i] == '_')
				return (1);
			else if (ft_isdigit(str[i]) || str[i] == '=' || str[i] == '\0')
				return (0);
		}
		return (0);
	}
	if (c == '/')
	{
		while (str[++i] != '=')
			if (str[i] == '/')
				return (0);
		return (1);
	}
	if (ft_isalpha(c) || c == '_' || c == '=')
		return (1);
	return (0);
}

void	export_error_message(char *str)
{
	ft_putstr_fd("MiniBoosted: export:'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	check_identifier(t_global *global, int j, int idx_args)
{
	int		i;
	char	*str;

	i = 0;
	str = global->struct_id[j].split_command[idx_args];
	while (global->struct_id[j].split_command[idx_args][i])
	{
		if (!ft_identifier(str[i], str))
		{
			export_error_message(global->struct_id[j].split_command[idx_args]);
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
		{
			return (i);
		}
	}
	return (-1);
}
// export a -> creer a sauf sil existe deja
//export a= ->
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
			// 	fprintf(stderr, "x\n");
			i = check_env(global, j, idx_args, stuff);
			if (i != -1)
				pa_pop(&global->personal_env, i);
			pa_add(&global->personal_env,
					ft_strdup(global->struct_id[j].split_command[idx_args]));
		}
		// else
		// 	export_error_message(global->struct_id[j].split_command[idx_args]);
	}
	return (0);
}

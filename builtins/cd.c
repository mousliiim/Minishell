/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:30 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/20 20:44:38 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	cd(t_global *global, int i)
{
	char	*env;

	if (!global->struct_id[i].split_command[1])
	{
		env = getenv("HOME");
		if (!env || !*env)
			ft_printf("miniboosted: cd: HOME : not set\n");
		else
			g_status = chdir(env);
		if (g_status != 0)
		{
			ft_putstr_fd("miniboosted: cd : ", 2);
			ft_putstr_fd(global->struct_id[i].split_command[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		if (global->nb > 1)
			exit(0);
		return (g_status);
	}
	g_status = chdir(global->struct_id[i].split_command[1]);
	if (g_status != 0)
	{
		ft_putstr_fd("miniboosted: cd : ", 2);
		ft_putstr_fd(global->struct_id[i].split_command[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (global->nb > 1)
		exit(0);
	return (g_status);
}

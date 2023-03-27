/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:30 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/27 22:41:58 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static void	cd_error_message(char *str, int choice)
{
	if (choice == 1)
	{
		ft_putstr_fd("miniboosted: cd: too many arguments\n", 2);
		g_status = 2;
		return ;
	}
	ft_putstr_fd("miniboosted: cd : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_status = 1;
}

static int	len_split_command(t_global *glo, int idx)
{
	int	i;

	i = 0;
	while (glo->struct_id[idx].split_command[i])
		i++;
	return (i);
}

int	cd(t_global *global, int i)
{
	char	*env;
	int		len;

	len = len_split_command(global, i);
	if (len > 2)
		return (cd_error_message(NULL, 1), 0);
	if (!global->struct_id[i].split_command[1] && !global->struct_id[i].head)
	{
		env = getenv("HOME");
		if (!env || !*env)
			ft_printf("MiniBoosted: cd: HOME : not set\n");
		else
			g_status = chdir(env);
		if (g_status != 0)
			return (cd_error_message(global->struct_id[i].split_command[1], 42),
				0);
		return (g_status);
	}
	if (!global->struct_id[i].split_command[1])
		return (0);
	g_status = chdir(global->struct_id[i].split_command[1]);
	if (g_status != 0)
		return (cd_error_message(global->struct_id[i].split_command[1], 42), 0);
	return (0);
}

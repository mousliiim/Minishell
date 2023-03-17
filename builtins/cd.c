/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:30 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/16 07:18:43 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd(t_global *global, int i)
{
	int		status;
	char	*env;

	status = 0;
	if (!global->struct_id[i].split_command[1])
	{
		env = getenv("HOME");
		if (!env)
			ft_printf("miniboosted: cd: HOME : not set\n");
		status = chdir(env);
		if (status != 0)
		{
			ft_putstr_fd("miniboosted: cd : ", 2);
			ft_putstr_fd(global->struct_id[i].split_command[1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		if (global->nb > 1)
			exit(0);
		return (status);
	}
	status = chdir(global->struct_id[i].split_command[1]);
	if (status != 0)
	{
		ft_putstr_fd("miniboosted: cd : ", 2);
		ft_putstr_fd(global->struct_id[i].split_command[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (global->nb > 1)
		exit(0);
	return (status);
}
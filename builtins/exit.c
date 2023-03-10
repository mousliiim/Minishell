/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:03:02 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/10 01:03:33 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_exit(t_global *global, int j)
{
	int	i;

	close(global->fd_solo_redirection);
	close(global->link[0]);
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

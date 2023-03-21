/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:24:20 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/21 23:47:49 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	ctrl_d(int status)
{
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	exit(status);
}

void	ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 130;
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

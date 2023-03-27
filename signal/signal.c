/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:24:20 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/27 21:35:07 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	handle_signal_waiting(int signal_number)
{
	if (signal_number == SIGINT)
		g_status = 130;
	else if (signal_number == SIGQUIT)
		g_status = 131;
}

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

void	ctrl_antislash(int sig)
{
	if (sig == SIGQUIT)
	{
		g_status = 131;
		exit(131);
	}
	if (sig == SIGINT)
	{
		g_status = 130;
		exit(130);
	}
}

void	quit_hd(int sign)
{
	t_global	*glo;

	(void)sign;
	write(1, "\n", 1);
	rl_clear_history();
	glo = NULL;
	glo = endton(glo);
	glo->nb_free = 0;
	glo->forkstates = 0;
	close(glo->link_heredoc[1]);
	close(glo->link_heredoc[0]);
	clear_lst(glo->struct_id, glo->nb);
	hd_free_inchild(glo);
	if (sign == 42)
		exit(42);
	exit(130);
}

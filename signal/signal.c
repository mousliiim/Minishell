/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:24:20 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/24 20:35:35 by mparisse         ###   ########.fr       */
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

void	ctrl_antislash(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	if (sig == SIGINT)
		exit(130);
}

void	quit_hd(int sign)
{
	t_global	*glo;

	(void) sign;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:06:20 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/14 23:44:06 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

t_global	*endton(t_global *glo)
{
	static t_global	*global;
	
	if (!glo)
		return (global);
	global = glo;
	return (global);
}

void	quit_hd(int sign)
{
	t_global	*glo;

	(void) sign;
	write(1, "\n", 1);
	glo = NULL;
	glo = endton(glo);
	glo->nb_free = 0;
	glo->forkstates = 0;
	close(glo->link_heredoc[1]);
	close(glo->link_heredoc[0]);
	free_inchild(glo);
	exit(130);
}

void	waiting_hd(t_global *global, int forkstate)
{
	int	status;

	status = 0;
	waitpid(forkstate, &status, 0);
	if (status == 130)
	g_status = status;
	global->status = status;
}

int	start_heredoc(t_global *glo, int j, t_list_mini *head)
{
	char	*str;
	// int		link_heredoc[2];
	char	*limit;
	int		forkstate;

	limit = head->file_name;
	pipe(glo->link_heredoc);
	signal(SIGINT, SIG_IGN);
	forkstate = fork();
	if (forkstate == 0)
	{
		signal(SIGINT, &quit_hd);
		while (1)
		{
			str = readline("here_doc:");
			if (!str)
				break ;
			str = catch_expand(glo, str);
			if (!ft_strcmp(str, limit))
				break ;
			ft_putendl_fd(str, glo->link_heredoc[1]);
		}
		close(glo->link_heredoc[1]);
		close(glo->link_heredoc[0]);
		exit(0);
	}
	waiting_hd(glo, forkstate);
	signal(SIGINT, &ctrl_c);
	close(glo->link_heredoc[1]);
	glo->struct_id[j].prev_heredocs = glo->link_heredoc[0];
	return (0);
}

void	catch_heredocs(t_global *glo, size_t nb_command)
{
	t_list_mini	*head;
	size_t		i;

	i = 0;
	glo->nb_hd = 0;
	while (i < nb_command)
	{
		glo->struct_id[i].prev_heredocs = -1;
		head = glo->struct_id[i].head;
		while (head)
		{
			if (head->redirect == HERE_DOC)
			{
				start_heredoc(glo, i, head);
				glo->nb_hd++;
			}
			head = head->next;
		}
		i++;
	}
}

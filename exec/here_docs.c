/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:06:20 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/27 23:01:29 by mmourdal         ###   ########.fr       */
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

static void	waiting_hd(t_global *global, int forkstate)
{
	int	status;

	status = 0;
	waitpid(forkstate, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	if (status == 130)
		global->here_doc_failed = 1;
	g_status = status;
	global->status = status;
}

static void	loop_here_docks(t_airdock *airdock, t_global *glo, t_list_mini *head)
{
	while (1)
	{
		airdock->str = readline("here_doc:");
		if (!airdock->str)
			break ;
		airdock->str = catch_expand(glo, airdock->str);
		if (!airdock->str)
		{
			ft_printf("Malloc failed in here docs\n");
			quit_hd(42);
		}
		if (!ft_strcmp(airdock->str, head->file_name))
			break ;
		ft_putendl_fd(airdock->str, glo->link_heredoc[1]);
		free(airdock->str);
	}
}

int	start_heredoc(t_global *glo, int j, t_list_mini *head, int nbhd)
{
	t_airdock	airdock;

	pipe(glo->link_heredoc);
	signal(SIGINT, SIG_IGN);
	airdock.forkstate = fork();
	line_positif(head->file_name);
	if (airdock.forkstate == 0)
	{
		signal(SIGINT, &quit_hd);
		loop_here_docks(&airdock, glo, head);
		hd_free_inchild(glo);
		if (airdock.str)
			free(airdock.str);
		return (close(glo->link_heredoc[1]), close(glo->link_heredoc[0]),
			exit(0), 0);
	}
	glo->struct_id[j].prev_heredocs = glo->link_heredoc[0];
	if (nbhd != glo->nb_hd)
		close(glo->link_heredoc[0]);
	close(glo->link_heredoc[1]);
	return (signal(SIGINT, &ctrl_c), waiting_hd(glo, airdock.forkstate), 0);
}

void	len_heredoc(t_global *glo, size_t nb_command)
{
	t_list_mini	*head;
	size_t		i;

	i = 0;
	glo->nb_hd = 0;
	while (i < nb_command)
	{
		head = glo->struct_id[i].head;
		while (head)
		{
			if (head->redirect == HERE_DOC)
				glo->nb_hd++;
			head = head->next;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:06:20 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/10 04:59:46 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	start_heredoc(t_global *glo, int j, t_list_mini *head)
{
	char	*str;
	int		link_heredoc[2];
	char	*limit;

	limit = head->file_name;
	pipe(link_heredoc);
	while (1)
	{
		str = readline("here_doc:");
		if (!str)
			break ;
		if (!ft_strcmp(str, limit))
			break ;
		ft_putendl_fd(str, link_heredoc[1]);
	}
	close(link_heredoc[1]);
	glo->struct_id[j].prev_heredocs = link_heredoc[0];
	return (0);
}

void	catch_heredocs(t_global *glo, size_t nb_command)
{
	t_list_mini	*head;
	size_t		i;

	i = 0;
	while (i < nb_command)
	{
		glo->struct_id[i].prev_heredocs = -1;
		head = glo->struct_id[i].head;
		while (head)
		{
			if (head->redirect == HERE_DOC)
				start_heredoc(glo, i, head);
			head = head->next;
		}
		i++;
	}
}

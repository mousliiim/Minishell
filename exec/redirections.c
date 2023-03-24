/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:07:05 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/24 22:16:44 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	openfiles(t_global *glo, int j)
{
	t_list_mini	*list;
	int			fd;

	list = glo->struct_id[j].head;
	while (list)
	{
		if (!*list->file_name && list->redirect != HERE_DOC)
			return (ft_printf("miniboosted: ambiguous redirect\n"), -1);
		if (list->redirect == OUT)
			fd = open(list->file_name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		else if (list->redirect == IN)
			fd = open(list->file_name, O_RDONLY);
		else if (list->redirect == APPEND)
			fd = open(list->file_name, O_CREAT | O_APPEND | O_WRONLY, 0666);
		else if (list->redirect == HERE_DOC)
			fd = glo->struct_id[j].prev_heredocs;
		if (fd == -1)
			return (perror("miniboosted"), -1);
		if (list->redirect == APPEND || list->redirect == OUT)
			dupnclose(fd, STDOUT_FILENO);
		if (list->redirect == IN || list->redirect == HERE_DOC)
			dupnclose(fd, STDIN_FILENO);
		list = list->next;
	}
	return (0);
}

int	openfiles_bt(t_global *glo, int j)
{
	t_list_mini	*list;
	int			fd;

	list = glo->struct_id[j].head;
	while (list)
	{
		if (!*list->file_name && list->redirect != HERE_DOC)
			return (ft_printf("miniboosted: ambiguous redirect\n"), -1);
		if (list->redirect == OUT)
			fd = open(list->file_name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		else if (list->redirect == IN)
			fd = open(list->file_name, O_RDONLY);
		else if (list->redirect == APPEND)
			fd = open(list->file_name, O_CREAT | O_APPEND | O_WRONLY, 0666);
		else if (list->redirect == HERE_DOC)
			fd = glo->struct_id[j].prev_heredocs;
		if (fd == -1)
			return (perror("miniboosted"), -1);
		if (list->redirect == APPEND || list->redirect == OUT)
			dupnclose(fd, STDOUT_FILENO);
		if (list->redirect == IN || list->redirect == HERE_DOC)
			close(fd);
		list = list->next;
	}
	return (0);
}

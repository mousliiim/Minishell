/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 07:07:05 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/22 18:42:37 by mparisse         ###   ########.fr       */
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

/*
	Comment and Errors:

	pwd not updated on cd !!!
	command: cd lol lol 
		-> returns: miniboosted: cd : lol: No such file or directory
		-> expected: bash: cd: too many arguments
	command: cd lol && echo $?
		-> returns code of 0
		-> expected to return 1
	command: cd when HOME is not set
		returns: nothing and return code is 0 so success, why ??
		expected: bash: cd: HOME not set
*/

// int	openfiles(t_global *glo, int j)
// {
// 	t_list_mini	*list;
// 	int			fd;

// 	list = glo->struct_id[j].head;
// 	fd = -1;
// 	while (list)
// 	{
// 		if (!*list->file_name && list->redirect != HERE_DOC)
// 			return (ft_printf("miniboosted: ambiguous redirect\n"), -1);
// 		if (list->redirect == OUT)
// 			fd = open(list->file_name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
// 		else if (list->redirect == IN)
// 			fd = open(list->file_name, O_RDONLY);
// 		else if (list->redirect == APPEND)
// 			fd = open(list->file_name, O_CREAT | O_APPEND | O_WRONLY, 0666);
// 		if (fd == -1 && list->redirect != HERE_DOC)
// 			return (perror("miniboosted"), -1);
// 		if (list->redirect == APPEND || list->redirect == OUT)
// 			dupnclose(fd, STDOUT_FILENO);
// 		if (list->redirect == IN)
// 			dupnclose(fd, STDIN_FILENO);
// 		if (list->redirect == HERE_DOC)
// 			dupnclose(glo->struct_id[j].prev_heredocs, STDIN_FILENO);
// 		list = list->next;
// 	}
// 	return (0);
// }

int	openfiles_bt(t_global *glo, int j)
{
	t_list_mini	*list;
	int			fd;

	list = glo->struct_id[j].head;
	while (list)
	{
		if (list->redirect == OUT)
			fd = open(list->file_name, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (list->redirect == APPEND)
			fd = open(list->file_name, O_CREAT | O_APPEND | O_WRONLY, 0666);
		if (list->redirect == IN)
			fd = open(list->file_name, O_RDONLY);
		if (fd == -1)
			return (perror("miniboosted"), -1);
		if (list->redirect == APPEND || list->redirect == OUT)
			dupnclose(fd, STDOUT_FILENO);
		if (list->redirect == IN)
			close(fd);
		else if (list->redirect == HERE_DOC)
		{
			if (!*list->file_name)
			{
				ft_printf("miniboosted: ambiguous redirect\n");
				return (-1);
			}
			close(glo->struct_id[j].prev_heredocs);
		}
		list = list->next;
	}
	return (0);
}

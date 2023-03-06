/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rafter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:32:34 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/06 01:57:27 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	return_redir_enum(char *line)
{
	int		i;
	t_type	type;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '>' && line[i + 1] != '>')
		return (type = OUT);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (type = IN);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (type = HERE_DOC);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (type = APPEND);
	return (0);
}

char	*return_file_name(char *line)
{
	int		i;
	int		j;
	char	*file_name;

	i = 0;
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	file_name = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	while (line[i] != '\0')
	{
		file_name[j] = line[i];
		i++;
		j++;
	}
	file_name[j] = '\0';
	return (file_name);
}

t_list_mini	*ft_lstlaste(t_list_mini *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list_mini	*ft_lstnewe(void *content, t_type type)
{
	t_list_mini	*ptr;

	ptr = malloc(sizeof(t_list_mini));
	if (!ptr)
		return (NULL);
	ptr->file_name = content;
	ptr->redirect = type;
	ptr->next = NULL;
	return (ptr);
}

void	ft_lstadde_back(t_list_mini **lst, t_list_mini *new)
{
	t_list_mini	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlaste(*lst);
		last->next = new;
	}
}

void display(t_list_mini *head)
{
	char		*display;
	t_list_mini	*temp;

	temp = head;
	ft_printf("\n*******************\nDISPLAY LINKED LIST : \n");
	while (temp != NULL)
	{
		if (temp->redirect == OUT)
			display = ">";
		else if (temp->redirect == IN)
			display = "<";
		else if (temp->redirect == HERE_DOC)
			display = "<<";
		else if (temp->redirect == APPEND)
			display = ">>";
		ft_printf("*******************\n");
		ft_printf("File_name : %s\n", temp->file_name);
		ft_printf("Type enum : %d\n", temp->redirect);
		ft_printf("View enum : %s\n", display);
		ft_printf("*******************\n");
		temp = temp->next;
	}
}

void	ft_lstcleare(t_list_mini **lst, void (*del)(void*))
{
	t_list_mini	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->file_name);
		free(*lst);
		*lst = tmp;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:43:14 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/10 01:53:41 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_lstcleare(t_list_mini **lst, void (*del)(void *))
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

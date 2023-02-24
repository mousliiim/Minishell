/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 01:24:26 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/12 03:20:46 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*keep;

	if (!lst || !del)
		return ;
	keep = *lst;
	while (*lst)
	{
		keep = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = keep;
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 03:21:56 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/12 03:30:22 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*keep;

	if (!lst || !f)
		return ;
	keep = lst;
	while (lst)
	{
		keep = lst->next;
		(*f)(lst->content);
		lst = keep;
	}
}

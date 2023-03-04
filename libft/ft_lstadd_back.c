/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:16:34 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/04 21:47:32 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

/*
#include <stdio.h>

int main()
{
	t_list *elem1;
	t_list *elem2;

	elem1 = ft_lstnew((void *)"lala");
	elem2 = ft_lstnew((void *)"wesh");
	//ft_lstadd_front(&elem1, elem2);
	printf("%s", (char *)elem2->content);
	//printf(
}
*/

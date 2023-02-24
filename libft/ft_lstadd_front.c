/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:22:26 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/11 21:58:36 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list	**lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>

int main()
{
	t_list *elem1;
	t_list *elem2;

	elem1 = ft_lstnew((void *)"lala");
	elem2 = ft_lstnew((void *)"wesh");
	ft_lstadd_front(&elem1, elem2);
	printf("%s", (char *)elem1->content);
}
*/

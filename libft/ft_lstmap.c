/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:49:28 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/15 02:13:24 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*begin;

	if (!del)
		return (NULL);
	res = ft_lstnew(f(lst->content));
	if (!res)
		return (NULL);
	begin = res;
	lst = lst->next;
	while (lst)
	{
		res->next = ft_lstnew(f(lst->content));
		if (!res->next)
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		res = res->next;
		lst = lst->next;
	}
	return (begin);
}
/*
#include <stdio.h>

void	*ok_to_ko(

int main()
{
	t_list *elem1 = ft_lstnew((void *)"ok");
	t_list *elem2 = ft_lstnew((void *)"ok");
	
	ft_lstadd_front(&elem2 , elem1);
	
	printf("%s \n", (char *)elem1->content);
	printf("%s \n", (char *)elem2->content); 

	
}*/

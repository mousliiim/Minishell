/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 23:08:18 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/13 13:06:19 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
/*
int main()
{
	t_list *elem1;
	t_list *elem2;

	elem1 = ft_lstnew((void *)"lala");
	elem2 = ft_lstnew((void *)"wesh");
	ft_lstadd_front(&elem1, elem2);
	ft_lstadd_front(&elem1, ft_lstnew("toptop"));
	ft_lstadd_front(&elem1, ft_lstnew("tiptop"));
	ft_lstadd_front(&elem1, ft_lstnew("lokfop"));
	printf("%s", (char *)elem1->next->content);
	printf("%s", (char *)ft_lstlast(elem1)->content); 
}*/

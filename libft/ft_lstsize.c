/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:16:34 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/11 23:00:50 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
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
	ft_lstadd_front(&elem1, ft_lstnew("toptop"));
	ft_lstadd_front(&elem1, ft_lstnew("tiptop"));
	ft_lstadd_front(&elem1, ft_lstnew("lokfop"));
	printf("%s", (char *)elem1->next->content);
	printf("%d", ft_lstsize(elem1)); 
}
*/

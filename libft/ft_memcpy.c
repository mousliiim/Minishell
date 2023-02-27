/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:36:19 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/27 01:01:19 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*destcp;
	const char		*srccp;

	destcp = dest;
	srccp = src;
	if (dest == NULL && src == NULL)
	{
		return (0);
	}
	i = 0;
	while (i < n)
	{
		destcp[i] = srccp[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <assert.h>

int main()
{
	char *nul = NULL;
	char *autrenul = NULL;

	(void) nul;
	(void) autrenul;

	char *resof = memcpy("ok", nul, 0);
	char *res = ft_memcpy("ok", nul, 0);

	(void) resof;
	(void) res;
	printf("resof ; %s \nres : %s", resof, res);


	//assert(ft_memcpy("ok", nul, 1) == memcpy("ok",autrenul, 1));
}*/

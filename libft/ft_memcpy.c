/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:36:19 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/14 21:13:59 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	if (!src && !dest)
		return (NULL);
	str = (unsigned char *)dest;
	while (i < n)
	{
		str[i] = *(unsigned char *)src;
		i++;
		src++;
	}
	dest = str;
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

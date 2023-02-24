/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:59:29 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/10 15:18:27 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *ndl, size_t len)
{
	unsigned char	*str;
	size_t			i;
	size_t			j;
	size_t			keep;

	i = 0;
	j = 0;
	str = (unsigned char *)s;
	if (ft_strlen(ndl) == 0 || str == (unsigned char *)ndl)
		return ((char *)str);
	while (i < len && str[i])
	{
		if (str[i] == ndl[j])
		{
			keep = i;
			while (str[keep++] == ndl[j++])
			{
				if (j == ft_strlen(ndl) && keep <= len)
					return ((char *)str + i);
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main()
{
	char haystack[30] = "aaabcabcd";
	char needle[10] = "aabc";
	printf("res : %s", ft_strnstr(haystack, needle, 0));
}*/

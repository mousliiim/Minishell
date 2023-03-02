/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:52:17 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/02 02:50:26 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;

	if ((!dst || (!src)) && size == 0)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int main()
{
	char dest1[0xF00];
	char dest2[0xF00];
	char *str = "the cake is a lie!\0I'm hidden lol\r\n";
	//printf("%ld", ft_strlen(str));
	memset(dest1, 'A', sizeof(dest1) - 1);
	memset(dest2, 'A', sizeof(dest2) - 1);

	size_t i = strlcpy(dest1, str, 0);
	size_t j = ft_strlcpy(dest2, str, 0);
	printf("dest 1 (strlcpy)    : %s \n", dest1);
	printf("dest 2 (ft_strclpy) : %s \n", dest2);

	printf("i : %ld \n", i);
	printf("j : %ld", j);

	// dest : "the cake is a lie!\0I'm hidden lol\r\n"
	//char *src = "wesh";
	//size_t t = ft_strlcpy(dest, src, t);
}*/

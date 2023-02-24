/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:16:21 by mparisse          #+#    #+#             */
/*   Updated: 2022/10/17 23:30:25 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		len_src;
	size_t		len_dst;
	size_t		i;
	size_t		j;
	size_t		i_max;

	if ((!dst || (!src)) && size == 0)
		return (0);
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	i_max = size - len_dst - 1;
	if (size <= (len_dst + 1))
	{
		if (size == len_dst + 1)
			return (size + len_src - 1);
		return (len_src + size);
	}
	j = len_dst;
	while (src[i] && i < i_max)
	{
		dst[j++] = src[i++];
	}
	dst[j] = '\0';
	return (len_dst + len_src);
}

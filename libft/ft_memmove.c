/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:56:05 by mparisse          #+#    #+#             */
/*   Updated: 2022/10/20 17:27:11 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*t_dest;
	unsigned char	*t_src;

	if (((!src || !dest) && n == 0) || (!src && !dest))
		return (NULL);
	t_dest = (unsigned char *)dest;
	t_src = (unsigned char *)src;
	if (t_dest > t_src)
	{
		while (n-- > 0)
		{
			t_dest[n] = t_src[n];
		}
	}
	else
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}

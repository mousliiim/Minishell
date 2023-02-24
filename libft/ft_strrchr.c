/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:54:32 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/07 13:13:03 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*str;
	char		to_find;
	size_t		i;

	str = (char *)s;
	to_find = (char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (str[i] == to_find)
			return (str + i);
		i--;
	}
	if (str[i] == to_find)
		return (str);
	return (NULL);
}

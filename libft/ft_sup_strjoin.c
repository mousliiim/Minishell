/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sup_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 06:33:01 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/20 20:44:17 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_sup_strjoin(char const *s1, char c, char const *s2)
{
	char		*str;
	size_t		i;
	size_t		lens1;
	size_t		lens2;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	lens1 = ft_strlen(s1) + 1;
	lens2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (lens1 + lens2 + 2));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i] = c;
	i = 0;
	while (s2[i])
	{
		str[lens1++] = s2[i];
		i++;
	}
	str[lens1] = '\0';
	return (str);
}

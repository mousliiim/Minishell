/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:27:33 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/10 15:10:00 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)s;
	while (s[i] && (s[i] != (char)c))
	{
		i++;
	}
	if (str[i] == '\0' && c != '\0')
		return (NULL);
	return (str + i);
}
/*
#include <stdio.h>

int main()
{
	char s[] = "tripouille";
	char *ret = strchr(s, 'z');
	printf("%s", ret);
}*/

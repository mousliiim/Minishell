/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:44:01 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/06 20:53:54 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr3(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char) c)
		s++;
	if (*s == (char) c)
		return (s);
	return (NULL);
}

size_t	ft_strlen2(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin3(char *buffer, char *str)
{
	char	*mstr;
	int		i;
	int		j;

	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char) * 1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	if (!str || !buffer)
		return (NULL);
	mstr = malloc(sizeof(char) * (ft_strlen2(buffer) + ft_strlen2(str) + 1));
	if (!mstr)
		return (NULL);
	i = -1;
	while (buffer[++i])
		mstr[i] = buffer[i];
	j = 0;
	while (str[j])
		mstr[i++] = str[j++];
	mstr[i] = '\0';
	free(buffer);
	return (mstr);
}

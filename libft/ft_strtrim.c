/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:42:34 by mparisse          #+#    #+#             */
/*   Updated: 2022/11/10 18:40:44 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_psisset(const char c, const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_get_size(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ft_psisset(s1[i++], s2) == 1)
		j++;
	if (j == ft_strlen(s1))
		return (0);
	i = ft_strlen(s1) - 1;
	while (ft_psisset(s1[i--], s2) == 1)
		j++;
	i = ft_strlen(s1);
	return (i - j);
}

char	*ft_strtrim(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	size;
	size_t	j;

	if (!s1)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_get_size(s1, s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (ft_psisset(s1[i], s2) == 1)
		i++;
	while (j < size)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

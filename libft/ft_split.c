/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:45:12 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/25 03:09:58 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_c(char chr, char c)
{
	if (chr == c || c == '\t')
		return (1);
	return (0);
}

static int	get_size(char const *s, char c)
{
	size_t	i;
	size_t	cpt;

	cpt = 1;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (is_c(c, s[i]) == 1 && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		while (is_c(c, s[i]) == 0 && s[i])
			i++;
		cpt++;
	}
	return (cpt);
}

static char	**in_case(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	j = 0;
	i = 0;
	tab = malloc(sizeof(char *) * get_size(s, c));
	if (!tab || !s)
		return (NULL);
	while (j < get_size(s, c) && s[i])
	{
		while (is_c(c, s[i]) == 1 && s[i])
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (is_c(c, s[i]) == 0 && s[i])
			i++;
		tab[j] = ft_substr(s, start, i - start);
		if (!tab[j++])
			return (in_case(tab, j - 1));
	}
	tab[j] = 0;
	return (tab);
}
/*
#include <stdio.h>

int main()
{
	char **ret = ft_split(NULL,'6');
	(void) ret;
	printf("%s", ret[0]);
}
int main()
{
	int i = 0;
	char *str = "                    ";
	char **tab = ft_split(str, ' ');
	(void) i;
	(void) str;
	(void) tab;
	printf("%s \n", tab[0]);
	
	//if (str[ft_strlen(str) + 1] == '\0')
	//	printf("wesh");
	//printf("%ld", ft_strlen(str) + 1);	
	while (i < 2)
	{
		printf("str %d : %s \n", i , tab[i]);
		i++;
	}
}*/

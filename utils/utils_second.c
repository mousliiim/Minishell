/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:03:00 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/21 20:13:17 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

char	*ft_strcpy(char *dest, const char *src, int choice)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (choice)
		dest[i++] = ' ';
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup2(char const *s, int choice)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s) + 2);
	if (str == NULL)
		return (0);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	if (choice)
		str[i++] = ' ';
	str[i] = '\0';
	return ((char *)str);
}

void	ft_strjoin2(char **line, const char *s1)
{
	char	*res;
	int		i;

	if (*line && **line)
	{
		i = 0;
		while ((*line)[i])
			i++;
		res = malloc(ft_strlen(s1) + i + 2);
		if (res)
		{
			ft_strcpy(res, *line, 1);
			ft_strcpy(res + i, s1, 1);
			free(*line);
			*line = res;
		}
		else
			return ;
		return ;
	}
	if (*line && !**line)
		free(*line);
	*line = ft_strdup2(s1, 1);
}

int	is_operator(char *c, int j)
{
	if (c[j] == '|' || c[j] == '<' || c[j] == '>'
		|| (c[j] == '>' && c[j + 1] == '>')
		|| (c[j] == '<' && c[j + 1] == '<'))
		return (1);
	return (0);
}

void	line_positif(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(void) j;
	while (line[i])
	{
		if (line[i] && line[i] < 0)
			line[i] = line[i] * -1;
		i++;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:44:33 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/21 20:38:19 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ft_clean_quotes(char **line)
{
	int			i;
	int			j;
	char		*tmp;
	static char	delim = 0;

	i = 0;
	j = 0;
	if (line == NULL || *line == NULL)
		return (0);
	tmp = malloc(sizeof(char) * (ft_strlen(*line) + 1));
	if (!tmp)
		return (0);
	while ((*line)[i])
	{
		if (((*line)[i] == '"' || (*line)[i] == '\'') && delim == 0)
			delim = (*line)[i++];
		else if ((*line)[i] == delim)
			i++;
		else
			tmp[j++] = (*line)[i++];
	}
	tmp[j] = '\0';
	free(*line);
	*line = tmp;
	return (1);
}

char	**ft_have_two_word(char **tab)
{
	char	*tmp;
	char	*arg;
	char	**split;
	int		i;
	int		j;

	arg = NULL;
	split = NULL;
	i = 0;
	while (tab[i])
	{
		j = 0;
		if (i == 0 && !check_first_char(tab[0]))
		{
			tmp = ft_substr(tab[i], 0, ft_strlen(tab[i]));
			if (!tmp)
				return (NULL);
			ft_strjoin2(&arg, tmp);
			if (!arg)
				return (NULL);
			free(tmp);
		}
		while (ft_isspace(tab[i][j]))
			j++;
		while (tab[i][j])
		{
			if (ft_isspace(tab[i][j]))
			{
				while (ft_isspace(tab[i][j]))
					j++;
				if (tab[i][j] && !ft_isspace(tab[i][j]))
				{
					if (i == 0)
						break ;
					tmp = ft_strndup(tab[i] + j, ft_strlen(tab[i]) - j);
					if (!tmp)
						return (NULL);
					ft_strjoin2(&arg, tmp);
					free(tmp);
					if (!arg)
						return (NULL);
					break ;
				}
			}
			if (!tab[i][j])
				break ;
			j++;
		}
		i++;
	}
	if (arg)
	{
		split = ft_split(arg, ' ');
		free(arg);
	}
	return (split);
}

static int	cut_raft(char **res, char *line, int *array[5])
{
	int		*i;
	int		*j;
	int		*k;
	int		**flag;

	i = array[0];
	j = array[1];
	k = array[2];
	flag = (int *[2]){array[3], array[4]};
	while (line[*i + *flag[1]] == '>' || line[*i + *flag[1]] == '<')
		(*flag[1]) += 1;
	if (!*flag[0])
	{
		res[(*j)] = ft_substr(line, *k, *i - *k);
		if (!res[(*j)++])
			return (0);
	}
	else
		*flag[0] = 0;
	res[(*j)] = ft_substr(line, *i, *flag[1]);
	if (!res[(*j)++])
		return (0);
	*i += *flag[1] == 2;
	*k = *i + 1;
	return (1);
}

char	**ft_split_rafter(char *line)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	int		flag[2];

	i = -1;
	j = 0;
	k = 0;
	flag[0] = check_first_char(line) > 0;
	res = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!res)
		return (NULL);
	while (line[++i])
	{
		flag[1] = 0;
		if (line[i] == '>' || line[i] == '<')
			cut_raft(res, line, (int *[5]){&i, &j, &k, &flag[0], &flag[1]});
	}
	res[j] = ft_substr(line, k, i - k);
	if (!res[j++])
		return (NULL);
	res[j] = NULL;
	return (res);
}

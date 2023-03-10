/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:44:33 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/10 22:18:05 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ft_clean_quotes(char **line)
{
	int		i;
	int		j;
	int		k;
	int		delim;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	(void) k;
	if (line == NULL || *line == NULL)
		return (0);
	tmp = ft_strdup(*line);
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			delim = i;
			i++;
			while (tmp[i] != tmp[delim])
			{
				(*line)[j] = tmp[i];
				i++;
				j++;
			}
		}
		else
		{
			(*line)[j] = tmp[i];
			j++;
		}
		i++;
	}
	(*line)[j] = '\0';
	free(tmp);
	return (1);
}

int	quote_checker(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 1;
	while (line[i])
	{
		if (line[i] == '"' && double_quote == 1 && single_quote == 0)
			double_quote = 0;
		else if (line[i] == '"' && double_quote == 0 && single_quote == 0)
			double_quote = 1;
		else if (line[i] == '\'' && double_quote == 1 && single_quote == 0)
			single_quote = 1;
		else if (line[i] == '\'' && double_quote == 1 && single_quote == 1)
			single_quote = 0;
		i++;
	}
	if (single_quote == double_quote)
		return (0);
	return (1);
}

int	is_operator(char *c, int j)
{
	if (c[j] == '|' || c[j] == '<' || c[j] == '>'
		|| (c[j] == '>' && c[j + 1] == '>')
		|| (c[j] == '<' && c[j + 1] == '<'))
		return (1);
	return (0);
}

void	line_negatif(char *line)
{
	int	i;
	int	j;
	int	delim;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			delim = i;
			j = i + 1;
			while (line[j] && line[j] != line[delim])
			{
				if (ft_isspace(line[j]) || is_operator(line, j))
					line[j] = line[j] * -1;
				j++;
			}
			i = j;
		}
		if (!line[i])
			break ;
		i++;
	}
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

int	rafter_check(char *str, int i, int *flag, int choice)
{
	int	j;

	flag[0] = 0;
	if (choice == 1)
		j = i + 1;
	else
		j = i + 2;
	if (str[j] == '<' || str[j] == '>')
		return (0);
	while (ft_isspace(str[j]))
		j++;
	if (is_operator(str, j))
		return (0);
	if (str[j] == '\0')
		return (0);
	while (str[j])
	{
		if (flag[0] == 0 && is_operator(str, j))
			break ;
		if (flag[0] == 0 && str[j] && !ft_isspace(str[j]) 
			&& !is_operator(str, j))
		{
			flag[1] = 0;
			break ;
		}
		j++;
	}
	return (1);
}

int	rafter_checker(char *str)
{
	int	i;
	int	flag[2];

	i = 0;
	flag[0] = 1;
	flag[1] = 1;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
		{
			if (!rafter_check(str, i, flag, 2))
				return (0);
		}
		else if ((str[i] == '<' || str[i] == '>')
			&& (str[i + 1] != '<' || str[i + 1] != '>'))
			if (!rafter_check(str, i, flag, 1))
				return (0);
		if (flag[0] != flag[1])
			return (0);
		i++;
	}
	return (1);
}

int	pipe_checker(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
		return (0);
	while (line[i])
	{
		if (i == 0 && line[i] == '|')
			return (0);
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
				return (0);
			if (line[i + 1] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

int	count_raft(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
			count++;
		else if (line[i] == '>' && line[i + 1] == '>')
			count++;
		else if (line[i] == '<' || line[i] == '>')
			count++;
		i++;
	}
	return (count);
}

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
		return ;
	}
	if (*line && !**line)
		free(*line);
	*line = ft_strdup2(s1, 1);
}

char	**ft_have_two_word(char **tab)
{
	char	*tmp;
	char	*arg;
	char	**split;
	int		i;
	int		j;

	arg = NULL;
	i = 0;
	while (tab[i])
	{
		j = 0;
		if (i == 0 && !check_first_char(tab[0]))
		{
			tmp = ft_substr(tab[i], 0, ft_strlen(tab[i]));
			ft_strjoin2(&arg, tmp);
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
					ft_strjoin2(&arg, tmp);
					free(tmp);
					break ;
				}
			}
			if (!tab[i][j])
				break ;
			j++;
		}
		i++;
	}
	if (arg == NULL)
		return (NULL);
	split = ft_split(arg, ' ');
	return (split);
}

char **ft_split_rafter(char *line)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	int		flag;

	if (check_first_char(line))
		flag = 1;
	else
		flag = 0;
	i = 0;
	j = 0;
	k = 0;
	res = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1] == '>')
		{
			if (flag == 0)
			{
				res[j] = ft_substr(line, k, i - k);
				j++;
				res[j] = ft_substr(line, i, 2);
				j++;
				i += 1;
				k = i + 1;
			}
			else
			{
				res[j] = ft_substr(line, i, 2);
				j++;
				i++;
				k = i + 1;
				flag = 0;
			}
		}
		else if (line[i] == '>' && line[i + 1] != '>')
		{
			if (flag == 0)
			{
				res[j] = ft_substr(line, k, i - k);
				j++;
				res[j] = ft_substr(line, i, 1);
				j++;
				k = i + 1;
			}
			else
			{
				res[j] = ft_substr(line, i, 1);
				j++;
				k = i + 1;
				flag = 0;
			}
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			if (flag == 0)
			{
				res[j] = ft_substr(line, k, i - k);
				j++;
				res[j] = ft_substr(line, i, 2);
				j++;
				i += 1;
				k = i + 1;
			}
			else
			{
				res[j] = ft_substr(line, i, 2);
				j++;
				i++;
				k = i + 1;
				flag = 0;
			}
		}
		else if (line[i] == '<' && line[i + 1] != '<')
		{
			if (flag == 0)
			{
				res[j] = ft_substr(line, k, i - k);
				j++;
				res[j] = ft_substr(line, i, 1);
				j++;
				k = i + 1;
			}
			else
			{
				res[j] = ft_substr(line, i, 1);
				j++;
				k = i + 1;
				flag = 0;
			}
		}
		i++;
	}
	res[j] = ft_substr(line, k, i - k);
	j++;
	res[j] = NULL;
	return (res);
}
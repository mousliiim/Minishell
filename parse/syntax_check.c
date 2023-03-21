/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:16:34 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/21 20:40:36 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

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

int	rafter_check(char *str, int i, int *flag, int choice)
{
	int	j;

	flag[0] = 0;
	if (choice == 1)
		j = i + 1;
	else
		j = i + 2;
	while (ft_isspace(str[j]))
		j++;
	if (is_operator(str, j) || str[j] == '\0')
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
			while (ft_isspace(line[i + 1]))
				i++;
			if (line[i + 1] == '|')
				return (0);
		}
		i++;
	}
	return (1);
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

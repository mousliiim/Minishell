/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:44:33 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/28 01:45:53 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int is_operator(char *c, int j)
{
	if (c[j] == '|' || c[j] == '<' || c[j] == '>' || (c[j] == '>' && c[j + 1] == '>') || (c[j] == '<' && c[j + 1] == '<'))
		return (1);
	return (0);
}

void line_negatif(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			j = i + 1;
			while (line[j] && (line[j] != '"' || line[j] == '\''))
			{
				if (line[j] == '"' || line[j] == '\'')
					break ;
				if (ft_isspace(line[j]) || is_operator(line, j))
					line[j] = line[j] * -1;
				j++;
			}
		}
		i++;
	}
}

void line_positif(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			j = i + 1;
			while (line[j] && (line[j] != '"' || line[j] == '\''))
			{
				if (line[j] == '"' || line[j] == '\'')
					break ;
				if (ft_isspace(line[j]) || is_operator(line, j))
					line[j] = line[j] * -1;
				j++;
			}
		}
		i++;
	}
}

int	rafter_checker(char *str)
{
	int	i;
	int	j;
	int flag1;
	int flag2;
	
	i = 0;
	if ((ft_strlen(str) == 1 && (str[i] == '<' || str[i] == '>')) || ((ft_strlen(str) == 2 && (str[i] == '<' || str[i] == '>')) && (ft_isspace(str[i + 1]) && !str[i + 2])))
		return (0);
	if (ft_strlen(str) == 2 && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')))
		return (0);
	flag1 = 1;
	flag2 = 1;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>'))
		{
			flag1 = 0;
			j = i + 2;
			if (str[j] == '<' || str[j] == '>')
				return (0);
			while(ft_isspace(str[j]))
				j++;
			if (is_operator(str, j))
				return (0);
			if (str[j] == '\0')
				return (0);
			while (str[j])
			{
				if (flag1 == 0 && is_operator(str, j))
					break ;
				if (flag1 == 0 && str[j] && !ft_isspace(str[j]) && !is_operator(str, j))
					flag2 = 0;
				j++;
			}
		}
		else if ((str[i] == '<' || str[i] == '>') && (str[i + 1] != '<' || str[i + 1] != '>'))
		{
			flag1 = 0;
			j = i + 1;
			if (str[j] == '<' || str[j] == '>')
				return (0);
			while(ft_isspace(str[j]))
				j++;
			if (is_operator(str, j))
				return (0);
			if (str[j] == '\0')
				return (0);
			while (str[j])
			{
				if (flag1 == 0 && is_operator(str, j))
					break ;
				if (flag1 == 0 && str[j] && !ft_isspace(str[j]) && !is_operator(str, j))
				{
					flag2 = 0;
					break ;
				}
				j++;
			}
		}
		if (flag1 != flag2)
			return (0);
		i++;
	}
	return (1);
}
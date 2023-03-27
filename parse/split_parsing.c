/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:08:57 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/27 23:27:01 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int		g_status;

char	**ft_have_two_word(char **tab, int j)
{
	char	*tmp;
	char	*arg;
	char	**split;
	int		i;

	arg = NULL;
	tmp = NULL;
	i = -1;
	while (tab && tab[++i])
	{
		j = 0;
		first_command(tab, &arg, tmp, (int *[2]){&i, &j});
		while (tab[i][j])
		{
			if (ft_isspace(tab[i][j]))
				if (find_option(tab, &arg, tmp, (int *[2]){&i, &j}))
					break ;
			if (!tab[i][j++])
				break ;
		}
	}
	if (!arg)
		return (NULL);
	split = ft_split(arg, ' ');
	return (free(arg), split);
}

static t_split_line	split_line_c(char *s, int i, int go, t_split_line res)
{
	char	*tmp;

	if (i > go)
	{
		tmp = ft_substr(s, go, i - go);
		if (!tmp)
			return (res.strings.capacity = 0, res);
		pa_add(&res.strings, tmp);
		if (!res.strings.capacity)
			return (res.strings.capacity = 0, res);
	}
	return (res);
}

t_split_line	split_line(char *line)
{
	t_split_line	res;
	int				i;
	int				start;

	res.strings = pa_new();
	if (!res.strings.capacity)
		return (res);
	i = 0;
	while (1)
	{
		while (ft_isspace(line[i]))
			i++;
		start = i;
		while ((line[i] && line[i] != '|'))
			i++;
		res = split_line_c(line, i, start, res);
		if (!res.strings.capacity)
			return (free_double_str((char **)res.strings.array),
				res.strings.capacity = 0, res);
		if (!line[i])
			break ;
		i++;
	}
	ft_clean_quotes((char **)res.strings.array);
	return (res);
}

static void	ft_free_input(t_tab_struct *tab_struct, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (tab_struct[i].split_command)
			free_double_str(tab_struct[i].split_command);
		if (tab_struct[i].commands)
			free_double_str(tab_struct[i].commands);
		i++;
	}
}

int	split_input(t_split_line splitted_line, t_tab_struct *tab_struct)
{
	size_t		i;
	char		**array;

	i = 0;
	while (i < splitted_line.strings.size)
	{
		if (rafter_line(splitted_line.strings.array[i]))
		{
			if (!rafter_cut(tab_struct, splitted_line, i))
				return (ft_free_input(tab_struct, i), 0);
		}
		else
		{
			array = ft_split(splitted_line.strings.array[i], ' ');
			tab_struct[i].split_command = array;
		}
		before_exec_to_positif(tab_struct, i);
		i++;
	}
	return (1);
}

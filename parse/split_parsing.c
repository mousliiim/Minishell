/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:08:57 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/19 23:40:57 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int		g_status;

t_split_line	split_line(const char *line)
{
	t_split_line	res;
	int				i;
	char			*tmp;
	int				start;

	res.strings = pa_new();
	i = 0;
	while (1)
	{
		while (ft_isspace(line[i]))
			i++;
		start = i;
		while ((line[i] && line[i] != '|'))
			i++;
		if (i > start)
		{
			tmp = ft_substr(line, start, i - start);
			pa_add(&res.strings, tmp);
		}
		if (!line[i])
			break ;
		i++;
	}
	ft_clean_quotes((char **)res.strings.array);
	return (res);
}

void	before_exec_to_positif(t_tab_struct *tab_struct, int j)
{
	int	k;

	k = 0;
	if (tab_struct[j].split_command)
	{
		while (tab_struct[j].split_command[k])
		{
			line_positif(tab_struct[j].split_command[k]);
			k++;
		}
	}
	if (tab_struct[j].commands)
	{
		while (tab_struct[j].commands[k])
		{
			line_positif(tab_struct[j].commands[k]);
			k++;
		}
	}
}

void	split_input(t_split_line splitted_line, t_tab_struct *tab_struct)
{
	size_t		i;
	char		**array;

	i = 0;
	while (i < splitted_line.strings.size)
	{
		if (rafter_line(splitted_line.strings.array[i]))
			rafter_cut(tab_struct, splitted_line, i);
		else
		{
			array = ft_split(splitted_line.strings.array[i], ' ');
			tab_struct[i].split_command = array;
		}
		before_exec_to_positif(tab_struct, i);
		i++;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rafter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:32:34 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/11 21:30:07 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	rafter_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1] == '>')
			return (1);
		else if (line[i] == '>' && line[i + 1] != '>')
			return (1);
		else if (line[i] == '<' && line[i + 1] == '<')
			return (1);
		else if (line[i] == '<' && line[i + 1] != '<')
			return (1);
		i++;
	}
	return (0);
}

int	check_first_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '>' && line[i + 1] != '>')
		return (1);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (2);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (3);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (4);
	return (0);
}

void	rafter_cut(t_tab_struct *tab_struct, t_split_line splitted_line, int j)
{
	size_t	k;
	char *file_name;
	t_type type;

	tab_struct[j].split_command = ft_have_two_word(ft_split_rafter(splitted_line.strings.array[j]));
	tab_struct[j].commands = ft_split_rafter(splitted_line.strings.array[j]);
	if (tab_struct[j].split_command
		&& check_first_char(tab_struct[j].commands[0]))
	{
		tab_struct[j].commands = ft_split_rafter(splitted_line.strings.array[j]);
		k = 0;
		while (tab_struct[j].commands[k])
		{
			tab_struct[j].commands[k] = ft_no_take_first_word(return_file_name(tab_struct[j].commands[k]));
			k++;
		}
		k = 0;
		while (tab_struct[j].commands[k])
		{
			file_name = return_file_name(tab_struct[j].commands[k
					+ 1]);
			type = return_redir_enum(tab_struct[j].commands[k]);
			ft_lstadde_back(&tab_struct[j].head,
				ft_lstnewe(file_name, type));
			k += 2;
		}
	}
	else if (tab_struct[j].split_command
		&& !check_first_char(tab_struct[j].commands[0]))
	{
		tab_struct[j].commands = ft_split_rafter(splitted_line.strings.array[j]);
		k = 0;
		while (tab_struct[j].commands[k])
		{
			tab_struct[j].commands[k] = ft_no_take_first_word(return_file_name(tab_struct[j].commands[k]));
			k++;
		}
		k = 1;
		while (tab_struct[j].commands[k])
		{
			file_name = return_file_name(tab_struct[j].commands[k
					+ 1]);
			type = return_redir_enum(tab_struct[j].commands[k]);
			ft_lstadde_back(&tab_struct[j].head,
				ft_lstnewe(file_name, type));
			k += 2;
		}
	}
	else if (tab_struct[j].split_command == NULL)
	{
		k = 0;
		while (tab_struct[j].commands[k])
		{
			file_name = return_file_name(tab_struct[j].commands[k
					+ 1]);
			type = return_redir_enum(tab_struct[j].commands[k]);
			ft_lstadde_back(&tab_struct[j].head,
				ft_lstnewe(file_name, type));
			k += 2;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/24 05:45:35 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	parse(char *str)
{
	int	i;
	int	different_command;

	i = 0;
	if (str[0] == 0)
		return (0);
	different_command = 1;
	while (str[i])
	{
		if (str[i] == '|')
			different_command++;
		i++;
	}
	return (different_command);
}

t_split_line	split_line(const char *line)
{
	t_split_line	res;
	int				i;
	int				start;

	res.strings = pa_new();
	i = 0;
	while (1)
	{
		while (ft_isspace(line[i]))
			i++;
		start = i;
		while (line[i] && line[i] != '|')
			i++;
		if (i > start)
			pa_add(&res.strings, ft_substr(line, start, i - start));
		if (!line[i])
			break ;
		i++;
	}
	return (res);
}

int	main(int ac, char **av, char **env)
{
	int					nb_of_cmd;
	char				*input;
	static t_tab_struct	*tab_struct;
	t_split_line		splitted_line;

	if (ac != 1)
		return (0);
	while (42)
	{
		input = readline("$miniboosted: ");
		nb_of_cmd = parse(input);
		tab_struct = malloc(sizeof(t_tab_struct) * nb_of_cmd);
		splitted_line = split_line(input);
		printf("nb_of_cmd >> %d\n", nb_of_cmd);
		while (nb_of_cmd--)
		{
			tab_struct[nb_of_cmd].id = nb_of_cmd;
			tab_struct[nb_of_cmd].commands = splitted_line.strings.array[nb_of_cmd];
			printf("tab_struct[%d] >> %s\n", nb_of_cmd, (char *)tab_struct[nb_of_cmd].commands);
		}
		// splitted_line = split_line(input, 42);
		// tab_struct[0].line_split.strings.array[0] = splitted_line.strings.array[0];
		// // printf("tab_struct[0] >> %s\n", (char *)tab_struct[0].line_split.strings.array[0]);
	}
}
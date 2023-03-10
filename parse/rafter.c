/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rafter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:32:34 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/10 02:17:48 by mmourdal         ###   ########.fr       */
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

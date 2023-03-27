/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/27 02:22:32 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static int	valid_option(char *option)
{
	int	i;
	int	j;

	i = 0;
	if (!option || !option[0])
		return (0);
	if (option[i++] != '-')
		return (0);
	while (option[i])
	{
		if (option[i] == 'n')
		{
			j = i + 1;
			while (option[j] == 'n')
				j++;
			if (option[j])
				return (0);
			else
				return (1);
		}
		else
			return (0);
		i++;
	}
	return (0);
}

static int	is_hyphen(char **arg)
{
	int	j;

	j = 0;
	if (arg[1][0] == '-' && arg[1][1] != 'n')
	{
		j = 1;
		while (arg[j])
		{
			write(1, arg[j], ft_strlen(arg[j]));
			j++;
			if (arg[j])
				write(1, " ", 1);
		}
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

static void	print(char **arg, int i)
{
	int	have_option;

	have_option = (i > 1);
	if (is_hyphen(arg))
		return ;
	while (arg[i])
	{
		if (arg[i + 1])
			write(1, arg[i], ft_strlen(arg[i]));
		else
			write(1, arg[i], ft_strlen(arg[i]));
		i++;
		if (arg[i])
			write(1, " ", 1);
	}
	if (!have_option)
		write(1, "\n", 1);
}

int	echo(t_global *glo, int j)
{
	int		i;
	char	**s_cmd;

	s_cmd = glo->struct_id[j].split_command;
	i = 1;
	while (s_cmd[i] && valid_option(s_cmd[i]))
	{
		i++;
	}
	print(s_cmd, i);
	g_status = 0;
	return (0);
}

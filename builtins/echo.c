/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/26 22:20:11 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static int	valid_option(char *option)
{
	int	i;

	i = 0;
	if (!option || !option[0])
		return (0);
	if (option[i++] != '-')
		return (0);
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	print(char **arg, int i)
{
	int	have_option;

	have_option = (i > 1);
	while (arg[i])
	{
		if (arg[i + 1])
			printf("%s ", arg[i]);
		else
			printf("%s", arg[i]);
		i++;
	}
	if (!have_option)
		printf("\n");
}

int	echo(t_global *glo, int j)
{
	int		i;
	char	**s_cmd;

	s_cmd = glo->struct_id[j].split_command;
	i = 1;
	if (s_cmd[1] && s_cmd[1][0] == '-' && !s_cmd[1][1])
	{
		printf("- ");
		// return (0);
	}
	while (s_cmd[i] && valid_option(s_cmd[i]))
		i++;
	print(s_cmd, i);
	g_status = 0;
	return (0);
}

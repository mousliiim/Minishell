/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:02:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/27 04:43:11 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	identifier_last(int c, char *str)
{
	int	i;

	i = -1;
	if (c == ':')
	{
		while (str[++i] != '=')
		{
			if (str[i] == ':')
				return (0);
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

int	print_env(t_global *glo, int j)
{
	int	i;

	(void)j;
	i = -1;
	while (glo->personal_env.array[++i])
		printf("%s\n", (char *)glo->personal_env.array[i]);
	return (0);
}

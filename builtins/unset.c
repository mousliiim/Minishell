/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:52:04 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/20 23:08:50 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	unset(t_global *glo, int j)
{
	int		i;
	int		idx_args;
	int		stuff;

	if (glo->nb > 1)
		exit(0);
	idx_args = 1;
	g_status = 0;
	while (glo->struct_id[j].split_command[idx_args])
	{
		i = -1;
		while (glo->personal_env.array[++i])
		{
			stuff = ft_strchr((char *)glo->personal_env.array[i], '=')
				- (char *)glo->personal_env.array[i];
			if (!ft_strncmp(glo->struct_id[j].split_command[idx_args],
					(char *)glo->personal_env.array[i],
					stuff))
			{
				pa_pop(&glo->personal_env, i);
				break ;
			}
		}
		idx_args++;
	}
	return (0);
}

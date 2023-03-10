/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:49 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/10 01:06:30 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo(t_global *glo, int j)
{
	int		i;
	int		idx_args;
	int		option;
	size_t	len_expand;

	idx_args = 1;
	option = 0;
	while (glo->struct_id[j].split_command[idx_args] && !ft_strcmp(glo->struct_id[j].split_command[idx_args], "-n"))
	{
		idx_args++;
		option = 1;
	}
	while (glo->struct_id[j].split_command[idx_args])
	{
		if (glo->struct_id[j].split_command[idx_args][0] == '$')
		{
			if (!glo->struct_id[j].split_command[idx_args][1])
				printf("$");
			else
			{
				i = 0;
				len_expand = ft_strlen(&glo->struct_id[j].split_command[idx_args][1]);
				while (glo->personal_env.array[i])
				{
					if (!ft_strncmp(&glo->struct_id[j].split_command[idx_args][1], (char *)glo->personal_env.array[i], len_expand))
					{
						if (!(char *)&glo->personal_env.array[i][len_expand + 1])
							break ;
						printf("%s", (char *)&glo->personal_env.array[i][len_expand + 1]);
						break ;
					}
					i++;
				}
			}
		}
		else
		{
			if (glo->struct_id[j].split_command[idx_args])
				printf("%s", glo->struct_id[j].split_command[idx_args]);
		}
		if (option == 0)
			printf("\n");
		else
			printf(" ");
		idx_args++;
	}
	if (glo->nb > 1)
		exit(0);
	return (0);
}

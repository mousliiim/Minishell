/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:27:00 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/09 04:01:38 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	display_split(t_tab_struct *tab_struct, t_global *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->nb)
	{
		j = 0;
		while (tab_struct[i].split_command[j])
		{
			if (j == 0 || tab_struct[i].split_command[j][0] == '<'
				|| tab_struct[i].split_command[j][0] == '>')
				fprintf(stderr, "CMD = %s\n", tab_struct[i].split_command[j]);
			else
				fprintf(stderr, "ARGS = %s\n", tab_struct[i].split_command[j]);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	print_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_printf("%s\n", str[i++]);
}

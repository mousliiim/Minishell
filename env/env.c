/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:02:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/10 05:07:14 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	print_env(t_global *glo, int j)
{
	int	i;

	(void) j;
	i = -1;
	while (glo->personal_env.array[++i])
		printf("%s\n", (char *)glo->personal_env.array[i]);
	if (glo->nb > 1)
		exit(0);
	return (0);
}

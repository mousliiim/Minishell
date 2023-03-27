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

int	print_env(t_global *glo, int j)
{
	int	i;

	(void)j;
	i = -1;
	while (glo->personal_env.array[++i])
		printf("%s\n", (char *)glo->personal_env.array[i]);
	return (0);
}

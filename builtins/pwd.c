/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:52:02 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/20 23:09:26 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	pwd(t_global *glo, int j)
{
	static char	pwdd[PATH_MAXIMUM] = {0};

	(void) j;
	(void) glo;
	g_status = 0;
	if (!getcwd(pwdd, PATH_MAXIMUM))
	{
		ft_printf("pwd: error retrieving current directory:");
		ft_printf("getcwd: cannot access parent directories: ");
		ft_printf("No such file or directory\n");
		g_status = 1;
	}
	else
		printf("%s\n", pwdd);
	return (0);
}

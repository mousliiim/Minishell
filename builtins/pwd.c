/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:52:02 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/10 04:39:35 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd(t_global *glo, int j)
{
	static char	pwdd[PATH_MAXIMUM] = {0};

	(void) j;
	if (!getcwd(pwdd, PATH_MAXIMUM))
	{
		ft_printf("pwd: error retrieving current directory:");
		ft_printf("getcwd: cannot access parent directories: ");
		ft_printf("No such file or directory\n");
	}
	else
		printf("%s\n", pwdd);
	if (glo->nb > 1)
		exit(0);
	return (0);
}
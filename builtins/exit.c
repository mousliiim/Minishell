/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:03:02 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/21 03:34:14 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;
#define DBL_MAX 1E+37

long long	ft_atoull(const char *str)
{
	int			neg;
	long long	res;

	res = 0;
	neg = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * neg);
}

// static int	is_space(char c)
// {
// 	if ((c >= '\t' && c <= '\r') || c == ' ')
// 		return (1);
// 	return (0);
// }

// static long long int	atoi_exit(const char *str)
// {
// 	long	res;
// 	int		negatif;

// 	res = 0;
// 	negatif = 1;
// 	while (is_space(*str) == 1)
// 		str++;
// 	if (*str == '+' || *str == '-')
// 	{
// 		if (*str == '-')
// 			negatif = negatif * -1;
// 		str++;
// 	}
// 	while (ft_isdigit(*str))
// 	{
// 		res = res * 10 + (*str - 48);
// 		str++;
// 	}
// 	return (res * negatif);
// }

int	builtin_exit(t_global *global, int j)
{
	int	i;

	close(global->link[0]);
	close(global->link[1]);
	if (global->fd_solo_redirection != -1)
		close(global->fd_solo_redirection);
	if (!global->struct_id[j].split_command[1])
	{
		free_inchild(global);
		exit(0);
	}
	i = 0;
	while (global->struct_id[j].split_command[1][i])
	{
		if (!ft_isdigit(global->struct_id[j].split_command[1][i]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(global->struct_id[j].split_command[1], 2);
			ft_putstr_fd(": numeric argument required", 2);
			free_inchild(global);
			exit(2);
		}
		i++;
	}
	if(ft_atoull(global->struct_id[j].split_command[1]) > DBL_MAX)
		printf("TEST\n");
	free_inchild(global);
	exit (i);
}


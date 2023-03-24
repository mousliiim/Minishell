/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:03:02 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/22 19:39:56 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;
#define LL_MAXOU 9223372036854775807UL

void	error_message_exit(char *str)
{
	ft_putstr_fd("miniboosted: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required", 2);
}

long long	ft_atoulld(const char *str)
{
	int						neg;
	int						i;
	unsigned long long		res;

	res = 0;
	neg = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
			neg *= -1;
		if (str[i] == '-')
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
		if (res > LL_MAXOU || (res > (LL_MAXOU + 1) && neg == -1))
			return (error_message_exit((char *)str), 2);
	}
	return ((long long)res * neg);
}

static int	ft_isdigit_special(int arg)
{
	if ((arg >= '0' && arg <= '9') || arg == '-' || arg == '+')
		return (1);
	return (0);
}

int	builtin_exit(t_global *global, int j)
{
	long long	i;

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
		if (!ft_isdigit_special(global->struct_id[j].split_command[1][i]))
		{
			error_message_exit(global->struct_id[j].split_command[1]);
			free_inchild(global);
			exit(2);
		}
		i++;
	}
	i = ft_atoulld(global->struct_id[j].split_command[1]);
	free_inchild(global);
	exit (i);
}

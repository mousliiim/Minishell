/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:34:48 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/09 04:01:42 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 7 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		if ((result * sign) > LLONG_MAX || (result * sign) < LLONG_MIN)
			exit(1);
		nptr++;
	}
	return (result * sign);
}
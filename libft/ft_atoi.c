/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:04:07 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/24 05:34:12 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

static int	is_space(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		negatif;

	res = 0;
	negatif = 1;
	while (is_space(*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negatif = negatif * -1;
		str++;
	}
	if (*str == '+' || *str == '-')
		return (ft_putstr_fd("Error\n", 1), exit(0), 0);
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - 48);
		str++;
		if (res > MAXOU_INT_MIN * -1)
			return (ft_printf("Error\n", 1), exit(0), 0);
	}
	if (negatif == -1 && res == (MAXOU_INT_MIN * -1) - 1)
		return (INT_MIN);
	return (res * negatif);
}
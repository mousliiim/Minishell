/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:52:04 by mparisse          #+#    #+#             */
/*   Updated: 2022/10/28 21:07:00 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int nb)
{
	int	i;

	i = (nb <= 0);
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		size;
	int		negative;
	int		nb1;

	nb1 = nb;
	negative = (nb <= 0);
	size = get_size(nb);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	size--;
	while (size >= 0)
	{
		str[size] = ft_abs(nb % 10) + 48;
		nb /= 10;
		size--;
	}
	if (negative == 1 && nb1 != 0)
		str[0] = '-';
	return (str);
}
/*
int main()
{
	int i = 0;
	char *str = ft_itoa(-623);
	while (str[i])
		printf("str i : %c \n", str[i++]);
	printf("str i : %d \n", str[i]);
	printf("str : %s", str);
}*/

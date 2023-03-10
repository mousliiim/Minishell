/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:40:37 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/09 09:40:38 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(const char *dest, const char *src)
{
	int		i;
	int		j;
	char	*new_dest;
	char	*new_src;

	new_dest = (char *)dest;
	new_src = (char *)src;
	i = 0;
	j = ft_strlen(new_dest);
	while (new_src[i])
	{
		new_dest[j] = new_src[i];
		i++;
		j++;
	}
	new_dest[j] = '\0';
	return (new_dest);
}


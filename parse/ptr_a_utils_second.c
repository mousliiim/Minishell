/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_a_utils_second.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:59:26 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/25 18:27:00 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pa_add(t_ptr_array *pa, void *new_str)
{
	if (pa->size == pa->capacity)
	{
		fprintf(stderr, "par ici\n");
		pa->capacity *= 2;
		pa->array = ft_realloc(pa->array, pa->size, pa->capacity
				* sizeof(void *));
		if (!pa->array)
		{
			pa->capacity = 0;
			return (0);
		}
	}
	pa->array[pa->size++] = new_str;
	return (1);
}

size_t	pa_size(t_ptr_array *pa)
{
	return (pa->size);
}

void	*pa_get(t_ptr_array *pa, size_t index)
{
	return (pa->array[index]);
}

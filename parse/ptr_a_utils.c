/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_a_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:47:19 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/10 02:17:13 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pa_pop_replace(t_ptr_array *array, size_t index, void *new)
{
	free(array->array[index]);
	array->array[index] = new;
	array->size--;
}

void	pa_pop(t_ptr_array *array, size_t index)
{
	free(array->array[index]);
	array->array[index] = 0;
	while (index < array->size)
	{
		array->array[index] = array->array[index + 1];
		index++;
	}
	array->size--;
}

t_ptr_array	pa_new(void)
{
	t_ptr_array	new;

	new.size = 0;
	new.capacity = 8;
	new.array = ft_calloc(sizeof(void *), 8);
	return (new);
}

void	pa_delete(t_ptr_array *pa)
{
	free(pa->array);
	pa->array = NULL;
}

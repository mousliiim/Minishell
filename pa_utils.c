/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:47:19 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/09 04:33:08 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdlib.h"

extern int	g_status;

void	*ft_realloc(void **old, size_t old_capacity, size_t new_capacity)
{
	void	**new;
	size_t	i;

	i = 0;
	new = ft_calloc(sizeof(void *), new_capacity);
	while (i < old_capacity)
	{
		new[i] = old[i];
		i++;
	}
	return (new);
}

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

void	pa_add(t_ptr_array *pa, void *new_str)
{
	if (pa->size == pa->capacity)
	{
		pa->capacity *= 2;
		pa->array = ft_realloc(pa->array, pa->size, pa->capacity
				* sizeof(void *));
	}
	pa->array[pa->size++] = new_str;
}

size_t	pa_size(t_ptr_array *pa)
{
	return (pa->size);
}

void	*pa_get(t_ptr_array *pa, size_t index)
{
	return (pa->array[index]);
}

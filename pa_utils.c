/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:24:02 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/27 23:18:16 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdlib.h"

void	*ft_realloc(void **old, size_t old_capacity, size_t	new_capacity)
{
	void	**new;
	size_t		i;

	i = 0;
	new = ft_calloc(sizeof(void *), new_capacity);
	while (i < old_capacity)
	{
		new[i] = old[i];
		i++;
	}
	// ft_memset(new[i], 0, new_capacity);
	return (new);
}

void	pa_pop(t_ptr_array	*array, size_t index)
{
	array->array[index] = 0;
	ft_memmove(array->array + index, array->array + index, array->size);
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
	// ft_printf("--> %p\n", pa -> array);
	free(pa->array);
	pa->array = NULL;
}

void	pa_add(t_ptr_array *pa, void *new_str)
{
	if (pa->size == pa->capacity)
	{
		pa->capacity *= 2;
		pa->array = ft_realloc(pa->array, pa->size,pa->capacity * sizeof(void *));
		// pa->array = realloc(pa->array, pa->capacity * sizeof(void *));
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

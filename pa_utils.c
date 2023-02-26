/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:24:02 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/26 21:04:27 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t realloc)
{
	void	*new;

	new = ft_calloc(sizeof(char), realloc);
	if (!new)
	{
		free(ptr);
		exit(1);
	}
	while (ptr++)
		new = ptr;
	free(ptr);
	return (new);
}

t_ptr_array	pa_new(void)
{
	t_ptr_array	new;

	new.size = 0;
	new.capacity = 8;
	new.array = malloc(sizeof(void *) * 8);
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
		pa->array = ft_realloc(pa->array, pa->capacity * sizeof(void *));
	}
	pa->array[pa->size++] = new_str;
}
//

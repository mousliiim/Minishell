/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:24:02 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/24 05:35:37 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(pa->array);
}

void	pa_add(t_ptr_array *pa, void *new_str)
{	
	if (pa->size == pa->capacity)
	{
		pa->capacity *= 2;
		pa->array = realloc(pa->array, pa->capacity * sizeof(void *));
	}
	pa->array[pa->size++] = new_str;
}


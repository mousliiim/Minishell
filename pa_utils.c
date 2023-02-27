/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 06:24:02 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/27 04:31:48 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "stdlib.h"

// void *
// ft_realloc(ptr, newSize)
//     char 	 *ptr;		/* Ptr to currently allocated block.  If
// 				 * it's 0, then this procedure behaves
// 				 * identically to malloc. */
//     unsigned int newSize;	/* Size of block after it is extended */
// {
//     unsigned int curSize;
//     char *newPtr;

//     if (ptr == 0) {
// 	return malloc(newSize);
//     }
//     curSize = Mem_Size(ptr);
//     if (newSize <= curSize) {
// 	return ptr;
//     }
//     newPtr = malloc(newSize);
//     bcopy(ptr, newPtr, (int) curSize);
//     free(ptr);
//     return(newPtr);
// }

// void	*ft_realloc(void *ptr, size_t realloc)
// {
// 	void	*new;

// 	new = ft_calloc(sizeof(char), realloc);
// 	if (!new)
// 	{
// 		free(ptr);
// 		exit(1);
// 	}
// 	while (ptr)
// 	{
// 		new = ptr++;
// 	}
// 	free(ptr);
// 	return (new);
// }

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
		pa->array = realloc(pa->array, pa->capacity * sizeof(void *));
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

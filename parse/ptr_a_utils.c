/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_a_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:47:19 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/25 18:29:23 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_option(char **tab, char **arg, char *tmp, int *array[2])
{
	int	*i;
	int	*j;

	while (ft_isspace(tab[*array[0]][*array[1]]))
		(*array[1])++;
	i = array[0];
	j = array[1];
	if (tab[*i][*j] && !ft_isspace(tab[*i][*j]))
	{
		if (*i == 0)
			return (1);
		tmp = ft_strndup(tab[*i] + *j, ft_strlen(tab[*i]) - *j);
		if (!tmp)
			return (0);
		ft_strjoin2(arg, tmp);
		free(tmp);
		if (!arg)
			return (0);
		return (1);
	}
	return (0);
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
	fprintf(stderr, "boucle\n");
	while (index < array->size)
	{
		array->array[index] = array->array[index + 1];
		index++;
	}
	array->size--;
}

// si ya un malloc qui foire dans split line 
// il faut que lon free tout ce que split line a alloue
// et on renvoie 0 dans loop shell comme ca lui peut free
// le reste
t_ptr_array	pa_new(void)
{
	t_ptr_array	new;

	new.size = 0;
	new.capacity = 8;
	new.array = ft_calloc(sizeof(void *), 8);
	if (!new.array)
	{
		new.capacity = 0;
		return (new);
	}
	return (new);
}

void	pa_delete(t_ptr_array *pa)
{
	free(pa->array);
	pa->array = NULL;
}

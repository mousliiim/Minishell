/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_a_utils_second.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:59:26 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/27 19:55:37 by mmourdal         ###   ########.fr       */
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

void	before_exec_to_positif(t_tab_struct *tab_struct, int j)
{
	int	k;

	k = 0;
	if (tab_struct[j].split_command)
	{
		while (tab_struct[j].split_command[k])
		{
			line_positif(tab_struct[j].split_command[k]);
			k++;
		}
	}
}

void	clean_quote(char **line, char *tmp, int ijc[3], int *delim)
{
	if (((*line)[ijc[0]] == '"' || (*line)[ijc[0]] == '\'') &&
			(ijc[2] == 0 || *delim != (*line)[ijc[0]]))
	{
		*delim = (*line)[ijc[0]];
		(ijc[0])++;
		(ijc[2])++;
	}
	else if ((*line)[ijc[0]] == *delim)
	{
		delim = 0;
		(ijc)[0]++;
		(ijc)[2]--;
	}
	else
	{
		tmp[ijc[1]] = (*line)[ijc[0]];
		(ijc)[0]++;
		(ijc)[1]++;
	}
}

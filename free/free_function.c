/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:30:47 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/20 18:11:22 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

void	hd_free_inchild(t_global *glo)
{
	size_t	i;

	fprintf(stderr, "free_inchild called2\n");
	i = 0;
	clear_lst(glo->struct_id, glo->nb);
	while (i < glo->nb)
	{
		free_double_str(glo->struct_id[i].split_command);
		free_double_str(glo->struct_id[i].commands);
		i++;
	}
	free(glo->struct_id);
	free_double_str((char **)glo->personal_env.array);
	// free_double_str(glo->path);
}


void	free_splitted_line(t_split_line *del)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = pa_size(&del->strings);
	while (i < size)
	{
		free(pa_get(&del->strings, i));
		i++;
	}
	pa_delete(&del->strings);
}

void	free_double_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_inchild(t_global *glo)
{
	size_t	i;

	fprintf(stderr, "free_inchild called\n");
	i = 0;
	clear_lst(glo->struct_id, glo->nb);
	while (i < glo->nb)
	{
		free_double_str(glo->struct_id[i].split_command);
		free_double_str(glo->struct_id[i].commands);
		i++;
	}
	free(glo->struct_id);
	free(glo->forkstates);
	free_double_str((char **)glo->personal_env.array);
	free_double_str(glo->path);
}

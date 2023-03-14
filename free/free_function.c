/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:30:47 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/14 07:06:09 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

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
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_inchild(t_global *glo)
{
	size_t	i;

	i = 0;
	// (void) i;
	while (i < glo->nb_free)
	{
		fprintf(stderr, "je rentre et je passe\n");
		free_double_str(glo->struct_id[i].split_command);
		i++;
	}
	free(glo->struct_id);
	free(glo->forkstates);
	free_double_str((char **)glo->personal_env.array);
	free_double_str(glo->path);
}

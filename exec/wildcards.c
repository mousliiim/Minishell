/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:42:19 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/17 19:47:07 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	size_cmd(t_global *glo, int idx)
{
	int	i;
	
	fprintf(stderr, "size cmd\n");
	i = 0;
	while (glo->struct_id[idx].split_command[i])
		i++;
	return (i);
}


int	len_wc(t_global *glo, int idx)
{
	int	i;
	int	j;
	int	wc;

	i = 0;
	wc = 0;
	while (glo->struct_id[idx].split_command[i])
	{
		j = 0;
		while (glo->struct_id[idx].split_command[i][j])
		{
			if (glo->struct_id[idx].split_command[i][j] == '*')
				wc++;
			j++;
		}
		i++;
	}
	if (wc == 1)
		return (wc);
	return (wc + 1);
}

int	fill_wc(t_global *glo, t_wildcards *wc, int len, int idx)
{
	int	i;
	int	j;
	int	idx_wc;

	i = 0;
	(void) j;
	(void) glo;
	idx_wc = 0;
	(void) wc;
	(void) len;
	(void) idx;
	// while (glo->struct_id[idx].split_command[i][j])
	return (0);
}

int	activate_wc(t_global *glo, int idx, int word_count)
{
	t_wildcards	*wc;
	int			len;
	int			i;
	(void) word_count;
	
	len = len_wc(glo, idx);
	fprintf(stderr, "len wc %d\n", len);
	wc = malloc(sizeof(t_wildcards) * len);
	i = 0;
	while (i < len)
		fill_wc(glo, wc, len, idx);
	// fill_wc();
	// char	**new_args;

	
	// if (cmd[0] == '*')
	// {
	// 	dent = readdir(dir);
	// 	while (dent != NULL)
	// 	{
			// len = ft_strlen(&cmd[1]);
			// len2 = ft_strlen(dent->d_name);
			// if (!ft_strncmp(&cmd[1], &dent->d_name[len2 - len], len))
	// 		{
	// 			word_count++;
	// 		}
	// 		dent = readdir(dir);
	// 	}
	// 	closedir(dir);
	// 	new_args = malloc(sizeof(char *) * (word_count + 1));
	// 	new_args[0] = ft_strdup(glo->struct_id[i].split_command[0]);
	// 	dir = opendir(".");
	// 	dent = readdir(dir);
	// 	j = 1;
	// 	while (dent != NULL)
	// 	{
	// 		len = ft_strlen(&cmd[1]);
	// 		len2 = ft_strlen(dent->d_name);
	// 		if (!ft_strncmp(&cmd[1], &dent->d_name[len2 - len], len))
	// 		{
	// 			new_args[j] = ft_strdup(dent->d_name);
	// 			j++;
	// 		}
	// 		dent=readdir(dir);
	// 	}
	// 	closedir(dir);
	// 	new_args[j] = 0;
	// 	glo->struct_id[i].split_command = new_args;
	// }
	// j = 0;
	return (0);
}
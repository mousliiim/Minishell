/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:42:19 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/18 01:03:56 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#define STAR '*'

int	size_cmd(t_global *glo, int idx)
{
	int	i;
	
	fprintf(stderr, "size cmd\n");
	i = 0;
	while (glo->struct_id[idx].split_command[i])
		i++;
	return (i);
}

// dans la commande je compte de *
// buil***.c

void	display_wc(t_wildcards *wc, int len)
{
	int			i;
	t_wildcards	*wc_ptr;

	i = 0;
	wc_ptr = wc;
	(void) len;
	fprintf(stderr, "wc ptr %p\n", wc);
	while (wc_ptr)
	{
		fprintf(stderr, "pattern[%d] >> %s\n",i, wc_ptr->pattern);
		wc_ptr = wc_ptr->next;
	}
}

t_wildcards	*ft_lstlast_wc(t_wildcards *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_wc(t_wildcards **lst, char *pattern)
{
	t_wildcards	*last;
	t_wildcards	*new;

	new = 0;
	if (!*lst)
	{
		fprintf(stderr, "here\n");
		new = malloc(sizeof(t_wildcards));
		new->pattern = pattern;
		new->next = NULL;
		*lst = new;
		return ;
	}
	else
	{
		last = ft_lstlast_wc(*lst);
		new = malloc(sizeof(t_wildcards));
		last->next = new;
		new->pattern = pattern;
		new->next = NULL;
	}
}

int	fill_wc(t_global *glo, t_wildcards **wc, char *to_split)
{
	int			i;
	char		**arg_star;

	i = 0;
	(void) glo;
	// (void) len;
	arg_star = ft_split(to_split, '*');
	while (arg_star[i])
	{
		ft_lstadd_back_wc(wc, arg_star[i]);
		i++;
	}
	return (0);
}

int	len_wc(t_global *glo, int idx)
{
	int	i;
	int	j;
	int	wc;
	int	len_in_word;

	i = 0;
	wc = 0;
	while (glo->struct_id[idx].split_command[i])
	{
		j = 0;
		len_in_word = 0;
		while (glo->struct_id[idx].split_command[i][j])
		{
			if (glo->struct_id[idx].split_command[i][j] == STAR)
			{
				while (glo->struct_id[idx].split_command[i][j] && glo->struct_id[idx].split_command[i][j] == '*')
					j++;
				if (!glo->struct_id[idx].split_command[i][j] && len_in_word)
					;
				else
					len_in_word++;
				// fprintf(stderr, "len >> %d\n", len_in_word);
			}
			if (!glo->struct_id[idx].split_command[i][j])
				break ;
			j++;
		}
		wc += len_in_word;
		i++;
	}
	return (wc);
}
// *buil*.c
// *buil*.c*
// buil*.c
// *.c
// 

int	activate_wc(t_global *glo, int idx, int word_count)
{
	t_wildcards	*wc;
	int			len;
	int			i;
	int			j;
	int			k;

	(void) word_count;
	len = len_wc(glo, idx);
	fprintf(stderr, "len wc %d\n", len);
	i = 0;
	j = 0;
	k = 0;
	wc = NULL;
	// i need to find the word with an * and split it in fill wc then fill it
	while (k < len)
	{
		while (glo->struct_id[idx].split_command[i])
		{
			j = 0;
			while (glo->struct_id[idx].split_command[i][j])
			{
				if (glo->struct_id[idx].split_command[i][j] == '*')
				{
					fill_wc(glo, &wc, glo->struct_id[idx].split_command[i]);
					k++;
					break ;
				}
				// fprintf(stderr, "third boucle\n");
				j++;
			}
			// fprintf(stderr, "second boucle\n");
			i++;
		}
		// fprintf(stderr, "first boucle\n");
	}
	glo->struct_id[idx].wc = wc;
	display_wc(glo->struct_id[idx].wc, len);
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
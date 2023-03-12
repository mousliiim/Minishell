/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:13:37 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/12 05:14:52 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

char	*find_expand(t_global *glo, char *find, int start, int end)
{
	int		i;
	int		stop;

	i = 0;
	if (end - start == 0)
		return("$");
	if (!ft_strcmp(find ,"?"))
		return (ft_itoa(g_status));
	while (glo->personal_env.array[i])
	{
		if (!ft_strncmp((char *)glo->personal_env.array[i], find, end - start))
		{
			stop = ft_strchr((char *)glo->personal_env.array[i], '=') - (char *)glo->personal_env.array[i];
			return ((char *)&glo->personal_env.array[i][stop + 1]);
		}
		i++;
	}
	return (0);
}

char	*catch_expand(t_global *glo, char *input)
{
	int		i;
	int		j;
	int		start;
	char	*to_replace_by;
	size_t	len_to_malloc;
	char	*new_input;

	i = 0;
	to_replace_by = 0;
	start = 0;
	len_to_malloc = ft_strlen(input);
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '$')
				i++;
			to_replace_by = find_expand(glo, &input[start], start, i);
			if (!to_replace_by)
				continue ;
			len_to_malloc += ft_strlen(to_replace_by);
			len_to_malloc -= i - start;
			continue ;
		}
		i++;
	}
	if (!start)
		return (input);
	new_input = malloc(sizeof(char) * len_to_malloc);
	j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '$')
			{
				i++;
			}
			to_replace_by = find_expand(glo, &input[start], start, i);
			if (!to_replace_by)
				continue ;
			ft_strcat(new_input, to_replace_by);
			j += ft_strlen(to_replace_by);
			continue ;
		}
		new_input[j] = input[i];
		j++;
		i++;
	}
	return (new_input);
}

int	have_expand(char *str)
{
	int		expand;
	size_t	i;

	expand = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}
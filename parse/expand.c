/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:13:37 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/27 23:12:09 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static void	line_negatif_expand(char *input)
{
	size_t	i;

	if (!input)
		return ;
	i = 0;
	while (input[i])
	{
		if (is_operator(input, i))
			input[i] = input[i] * -1;
		i++;
	}
}

static int	advance_idx(char *input, int *i, int *start, int *flag)
{
	if (input[*i] == '\'')
		*flag *= -1;
	if (*flag < 0)
		return (0);
	*start = *i + 1;
	(*i)++;
	if (ft_isdigit(input[*i]))
	{
		(*i)++;
		return (0);
	}
	while (input[*i] && (ft_isalnum(input[*i]) || (input[*i] == '_')))
		(*i)++;
	return (1);
}

static void	change_flags(char *input, int i, t_expand *expand)
{
	if (input[i] == '"' && expand->skip != -1)
		expand->skip = 42;
	if (input[i] == '\'' && expand->skip != 42)
		expand->skip *= -1;
}

size_t	get_replacement_size(t_global *glo, t_expand *exp, char *input,
		size_t len_to_malloc)
{
	exp->skip = 1;
	while (input[exp->i])
	{
		change_flags(input, exp->i, exp);
		if (input[exp->i] == '$')
		{
			if (advance_idx(input, &exp->i, &exp->start, &exp->skip))
			{
				exp->to_replace_by = find_expand(glo, &input[exp->start], exp);
				if (input[exp->i] == '?')
					exp->i++;
				if (!exp->to_replace_by)
					continue ;
				len_to_malloc += ft_strlen(exp->to_replace_by) - (exp->i
						- exp->start);
				continue ;
			}
		}
		if (!input[exp->i++])
			break ;
	}
	if (!exp->start)
		return (-1);
	return (len_to_malloc);
}

void	replace_variables(t_global *glo, t_expand *exp, char *input,
		char *new_input)
{
	exp->skip = 1;
	while (input[exp->i])
	{
		change_flags(input, exp->i, exp);
		if (input[exp->i] == '$')
		{
			if (advance_idx(input, &exp->i, &exp->start, &exp->skip))
			{
				exp->to_replace_by = find_expand(glo, &input[exp->start], exp);
				line_negatif_expand(exp->to_replace_by);
				if (input[exp->i] == '?')
					exp->i++;
				if (!exp->to_replace_by)
					continue ;
				ft_strcat(new_input, exp->to_replace_by);
				exp->j += ft_strlen(exp->to_replace_by);
				continue ;
			}
		}
		if (!input[exp->i])
			break ;
		new_input[exp->j++] = input[exp->i++];
	}
}

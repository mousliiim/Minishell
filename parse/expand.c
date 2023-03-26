/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:13:37 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/26 03:24:56 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

// $ >  $
// $? > status
// $?$ > status$
// $:$= > $:$=
// $HOME > variable env home
// \$HOME > $HOME
// $HOME4 > rien
// $9HOME > HOME
// $UID$HOME% > veuid vehome %
// $"" > rien
// "$""" > $
// pareil avec quote > $
// $"HOME" > HOME
// $''HOME > HOME
// pareil squote > HOME
// "$HO"ME > ME
// '$HO'ME > $HOME

/*
chose a demander a mouss

comment je peux mettre en negatif
les quotes apres le $
*/

void	mini_itoa(t_global *glo)
{
	int	tmp_status;
	int	i;

	tmp_status = g_status;
	i = (tmp_status == 0);
	while (tmp_status != 0)
	{
		tmp_status = tmp_status / 10;
		i++;
	}
	tmp_status = g_status;
	glo->str_status[i] = 0;
	i--;
	while (i >= 0)
	{
		glo->str_status[i] = ft_abs(tmp_status % 10) + 48;
		tmp_status /= 10;
		i--;
	}
}

char	*find_expand(t_global *glo, char *find, int start, int end, int skip)
{
	int	i;
	int	stop;

	i = 0;
	if (!ft_strncmp(find, "?", 1))
	{
		mini_itoa(glo);
		return (glo->str_status);
	}
	if (!(end - start))
	{
		if ((find[0] == '\'' || find[0] == '"') && skip == 1)
			return (0);
		return ("$");
	}
	while (glo->personal_env.array[i])
	{
		stop = ft_strchr((char *)glo->personal_env.array[i], '=')
			- (char *)glo->personal_env.array[i];
		if (!ft_strncmp(find, (char *)glo->personal_env.array[i], stop)
			&& stop == end - start)
			// return (&glo->personal_env.array[i][stop + 1]);
			return ((char *)(glo->personal_env.array[i] + stop + 1));
		i++;
	}
	return (0);
}

void	line_negatif_expand(char *input)
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

int	advance_idx(t_expand *expand, char *input, int i)
{
	if (expand->skip < 0)
		return (-1);
	if (expand->skip > 0)
	{
		expand->start = i + 1;
		i++;
		if (ft_isdigit(input[i]))
		{
			i++;
			return (-1);
		}
		while (input[i] && (ft_isalnum(input[i]) || (input[i] == '_')))
			i++;
	}
	return (i);
}

char	*catch_expand(t_global *glo, char *input)
{
	int		i;
	int		j;
	// int		start;
	int		skip;
	t_expand	expand;
	char	*to_replace_by;
	size_t	len_to_malloc;
	char	*new_input;

	i = 0;
	to_replace_by = 0;
	expand.start = 0;
	expand.skip = 1;
	len_to_malloc = ft_strlen(input);
	while (input[i])
	{
		if (input[i] == '"' && expand.skip != -1)
			expand.skip = 42;
		if (input[i] == '\'' && expand.skip != 42)
			expand.skip *= -1;
		if (input[i] == '$')
		{
				skip = advance_idx(&expand, input, i);
				if (skip == -1)
				{
					i++;
					continue ;
				}
				else
					i = skip;
				to_replace_by = find_expand(glo, &input[expand.start], expand.start, i, expand.skip);
				if (input[i] == '?')
					i++;
				if (!to_replace_by)
					continue ;
				len_to_malloc += ft_strlen(to_replace_by);
				len_to_malloc -= i - expand.start;
				continue ;
		}
		i++;
	}
	if (!expand.start)
		return (input);
	new_input = ft_calloc(sizeof(char), len_to_malloc);
	if (!new_input)
	{
		free_double_str((char **)glo->personal_env.array);
		ctrl_d(g_status);
		return (0);
	}
	expand.skip = 1;
	j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"' && expand.skip != -1)
			expand.skip = 42;
		if (input[i] == '\'' && expand.skip != 42)
			expand.skip *= -1;
		if (input[i] == '$')
		{
				skip = advance_idx(&expand, input, i);
				if (skip == -1)
				{
					i++;
					continue ;
				}
				else
					i = skip;
				while (input[i] && (ft_isalnum(input[i]) || (input[i] == '_')))
					i++;
				to_replace_by = find_expand(glo, &input[expand.start], expand.start, i, expand.skip);
				line_negatif_expand(to_replace_by);
				if (input[i] == '?')
					i++;
				if (!to_replace_by)
					continue ;
				ft_strcat(new_input, to_replace_by);
				j += ft_strlen(to_replace_by);
				continue ;
		}
		new_input[j++] = input[i++];
	}
	free(input);
	return (new_input);
}

			// if (input[i] == '\'')
			// 	expand.skip *= -1;
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:13:37 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/24 22:38:11 by mmourdal         ###   ########.fr       */
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

char	*find_expand(t_global *glo, char *find, int start, int end)
{
	int	i;
	int	stop;

	i = 0;
	stop = 0;
	if (!ft_strncmp(find, "?", end - start))
	{
		mini_itoa(glo);
		return (glo->str_status);
	}
	if (end - start == 0)
	{
		if (find[0] == '"' || find[0] == '\'')
			return (0);
		return ("$");
	}
	while (glo->personal_env.array[i])
	{
		stop = ft_strchr((char *)glo->personal_env.array[i], '=')
			- (char *)glo->personal_env.array[i];
		if (!ft_strncmp(find, (char *)glo->personal_env.array[i], stop)
			&& stop == end - start)
		{
			return (&glo->personal_env.array[i][stop + 1]);
		}
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

char	*catch_expand(t_global *glo, char *input)
{
	int		i;
	int		j;
	int		start;
	int		skip;
	char	*to_replace_by;
	size_t	len_to_malloc;
	char	*new_input;

	i = 0;
	to_replace_by = 0;
	start = 0;
	skip = 1;
	len_to_malloc = ft_strlen(input);
	while (input[i])
	{
		if (input[i] == '"' && skip != -1)
			skip = 42;
		if (input[i] == '\'' && skip != 42)
			skip *= -1;
		if (input[i] == '$')
		{
			if (skip > 0)
			{
				start = i + 1;
				i++;
				if (ft_isdigit(input[i]))
				{
					i++;
					continue ;
				}
				// while ((ft_isalnum(input[i]) || (input[i] == '_')) && input[i])
				while (input[i] && (ft_isalnum(input[i]) || (input[i] == '_') || (input[i] == '?')))
					i++;
				to_replace_by = find_expand(glo, &input[start], start, i);
				if (input[i] == '?')
					i++;
				if (!to_replace_by)
					continue ;
				len_to_malloc += ft_strlen(to_replace_by);
				len_to_malloc -= i - start;
				continue ;
			}
		}
		i++;
	}
	if (!start)
		return (input);
	new_input = ft_calloc(sizeof(char), len_to_malloc);
	if (!new_input)
		return (0);
	j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"' && skip != -1)
			skip = 42;
		if (input[i] == '\'' && skip != 42)
			skip *= -1;
		if (input[i] == '$')
		{
			if (input[i] == '\'')
				skip *= -1;
			if (skip > 0)
			{
				start = i + 1;
				i++;
				if (ft_isdigit(input[i]))
				{
					i++;
					continue ;
				}
				while (input[i] && (ft_isalnum(input[i]) || (input[i] == '_') || (input[i] == '?')))
					i++;
				to_replace_by = find_expand(glo, &input[start], start, i);
				line_negatif_expand(to_replace_by);
				if (input[i] == '?')
					i++;
				if (!to_replace_by)
					continue ;
				ft_strcat(new_input, to_replace_by);
				j += ft_strlen(to_replace_by);
				continue ;
			}
		}
		new_input[j] = input[i];
		j++;
		i++;
	}
	free(input);
	return (new_input);
}

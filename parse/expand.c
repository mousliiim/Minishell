/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 05:13:37 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/26 19:43:49 by mparisse         ###   ########.fr       */
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


char	*catch_expand(t_global *glo, char *input)
{
	int		tmp;
	size_t	len_to_malloc;
	char	*new_input;

	len_to_malloc = ft_strlen(input);
	tmp = get_replacement_size(glo, input, 0);
	if (tmp == -1)
		return (input);
	len_to_malloc = get_replacement_size(glo, input, len_to_malloc);
	if (!len_to_malloc)
		return (input);
	new_input = ft_calloc(sizeof(char), len_to_malloc);
	if (!new_input)
	{
		free_double_str((char **)glo->personal_env.array);
		ctrl_d(g_status);
		return (0);
	}
	replace_variables(glo, input, new_input);
	free(input);
	return (new_input);
}

// 0 i     1 start    2 skip
int	advance_idx(char *input, int *i, int *start, int *flag)
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
	return(1);
}

void	change_flags(char *input, int i, int *flag)
{
	if (input[i] == '"' && *flag != -1)
		*flag = 42;
	if (input[i] == '\'' && *flag != 42)
		*flag *= -1;
}

size_t	get_replacement_size(t_global *glo, char *input, size_t len_to_malloc)
{
	t_expand	expand;
	int		values[3];
	int		i;
	// char	*to_replace_by;

	i = 0; 
	expand.start = 0; 
	expand. = 1; 
	while (input[i])
	{
		change_flags(input, i, &values[2]);
		if (input[i] == '$')
		{
			if (advance_idx(input, &i, &expand.start, &values[2]))
			{
				expand.to_replace_by = find_expand(glo, &input[expand.start], expand.start, i, values[2]);
				if (input[i] == '?')
					i++;
				if (!expand.to_replace_by)
					continue ;
				len_to_malloc += ft_strlen(expand.to_replace_by);
				len_to_malloc -= i - expand.start;
				continue ;
			}
		}
		if (!input[i])
			break ;
		i++;
	}
	if (!values[1])
		return (-1);
	return (len_to_malloc);
}

void	replace_variables(t_global *glo, char *input, char *new_input)
{
	int		values[3];
	int		j;
	int		i;
	char	*to_replace_by;

	values[0] = 0; 
	values[1] = 0; 
	values[2] = 1;
	j = 0;
	i = 0;
	while (input[i])
	{
		change_flags(input, i, &values[2]);
		if (input[i] == '$')
		{
			if (advance_idx(input, &i, &values[1], &values[2]))
			{
				to_replace_by = find_expand(glo, &input[values[1]], values[1], i, values[2]);
				if (input[i] == '?')
					i++;
				if (!to_replace_by)
					continue ;
				ft_strcat(new_input, to_replace_by);
				j += ft_strlen(to_replace_by);
				continue ;
			}
		}
		if (!input[i])
			break ;
		new_input[j++] = input[i++];
	}
}

// size_t	handle_variable(t_global *glo, char *input, int *i, int *j, int *flag)
// {
// 	char	*to_replace_by;

// 	if (input[*i] == '$')
// 	{
// 		if (input[++(*i)] == '\'')
// 			*flag *= -1;
// 		if (*flag > 0)
// 		{
// 			*j = *i + 1;
// 			if (ft_isdigit(input[*i]))
// 			{
// 				(*i)++;
// 				return (0);
// 			}
// 			while (input[*i] && (ft_isalnum(input[*i]) || (input[*i] == '_')))
// 				(*i)++;
// 			to_replace_by = find_expand(glo, &input[*j], *j, *i, *flag);
// 			if (input[*i] == '?')
// 				(*i)++;
// 			if (!to_replace_by)
// 				return (0);
// 			return (ft_strlen(to_replace_by) - (*i - *j));
// 		}
// 	}
// 	return (0);
// }

// size_t	get_replacement_size(t_global *glo, char *input, size_t len_to_malloc)
// {
// 	int		i;
// 	int		j;
// 	int		flag;
// 	size_t	var_len;

// 	i = 0;
// 	j = 0;
// 	flag = 1;
// 	while (input[i])
// 	{
// 		if (input[i] == '"' && flag != -1)
// 			flag = 42;
// 		if (input[i] == '\'' && flag != 42)
// 			flag *= -1;
// 		var_len = handle_variable(glo, input, &i, &j, &flag);
// 		if (var_len > 0)
// 			len_to_malloc += var_len;
// 		else
// 			i++;
// 	}
// 	if (!j)
// 		return (0);
// 	return (len_to_malloc);
// }


// char	*catch_expand(t_global *glo, char *input)
// {
// 	int		i;
// 	int		j;
// 	int		values[1];
// 	int		values[2];
// 	char	*to_replace_by;
// 	size_t	len_to_malloc;
// 	char	*new_input;

// 	i = 0;
// 	to_replace_by = 0;
// 	start = 0;
// 	skip = 1;
// 	len_to_malloc = ft_strlen(input);
// 	while (input[i])
// 	{
// 		if (input[i] == '"' && skip != -1)
// 			skip = 42;
// 		if (input[i] == '\'' && skip != 42)
// 			skip *= -1;
// 		if (input[i] == '$')
// 		{
// 			if (skip > 0)
// 			{
// 				start = i + 1;
// 				i++;
// 				if (ft_isdigit(input[i]))
// 				{
// 					i++;
// 					continue ;
// 				}
// 				while (input[i] && (ft_isalnum(input[i]) || (input[i] == '_')))
// 					i++;
// 				to_replace_by = find_expand(glo, &input[start], start, i, skip);
// 				if (input[i] == '?')
// 					i++;
// 				if (!to_replace_by)
// 					continue ;
// 				len_to_malloc += ft_strlen(to_replace_by);
// 				len_to_malloc -= i - start;
// 				continue ;
// 			}
// 		}
// 		i++;
// 	}
// 	if (!start)
// 		return (input);
// 	new_input = ft_calloc(sizeof(char), len_to_malloc);
// 	if (!new_input)
// 	{
// 		free_double_str((char **)glo->personal_env.array);
// 		ctrl_d(g_status);
// 		return (0);
// 	}
// 	skip = 1;
// 	j = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '"' && skip != -1)
// 			skip = 42;
// 		if (input[i] == '\'' && skip != 42)
// 			skip *= -1;
// 		if (input[i] == '$')
// 		{
// 			if (input[i] == '\'')
// 				skip *= -1;
// 			if (skip > 0)
// 			{
// 				start = i + 1;
// 				if (ft_isdigit(input[++i]))
// 				{
// 					i++;
// 					continue ;
// 				}
// 				while (input[i] && (ft_isalnum(input[i]) || (input[i] == '_')))
// 					i++;
// 				to_replace_by = find_expand(glo, &input[start], start, i, skip);
// 				line_negatif_expand(to_replace_by);
// 				if (input[i] == '?')
// 					i++;
// 				if (!to_replace_by)
// 					continue ;
// 				ft_strcat(new_input, to_replace_by);
// 				j += ft_strlen(to_replace_by);
// 				continue ;
// 			}
// 		}
// 		new_input[j++] = input[i++];
// 	}
// 	free(input);
// 	return (new_input);
// }

// char	*catch_expand(t_global *glo, char *input)
// {
// 	int			i;
// 	int			j;
// 	// int		start;
// 	int			skip;
// 	t_expand	expand;
// 	char		*to_replace_by;
// 	size_t		len_to_malloc;

// 	i = 0;
// 	to_replace_by = 0;
// 	expand.start = 0;
// 	expand.skip = 1;
// 	len_to_malloc = ft_strlen(input);
// 	while (input[++i])
// 	{
// 		if (input[i] == '"' && expand.skip != -1)
// 			expand.skip = 42;
// 		if (input[i] == '\'' && expand.skip != 42)
// 			expand.skip *= -1;
// 		if (input[i] == '$')
// 		{
// 				skip = advance_idx(&expand, input, i);
// 				if (skip == -1)
// 				{
// 					i++;
// 					continue ;
// 				}
// 				else
// 					i = skip;
// 				to_replace_by = find_expand(glo, &input[expand.start], expand.start, i, expand.skip);
// 				if (input[i] == '?')
// 					i++;
// 				if (!to_replace_by)
// 					continue ;
// 				len_to_malloc += ft_strlen(to_replace_by);
// 				len_to_malloc -= i - expand.start;
// 				continue ;
// 		}
// 		i++;
// 	}
// 	if (!expand.start)
// 		return (input);
// 	expand.new_input = ft_calloc(sizeof(char), len_to_malloc);
// 	if (!expand.new_input)
// 	{
// 		free_double_str((char **)glo->personal_env.array);
// 		ctrl_d(g_status);
// 		return (0);
// 	}
// 	expand.skip = 1;
// 	j = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '"' && expand.skip != -1)
// 			expand.skip = 42;
// 		if (input[i] == '\'' && expand.skip != 42)
// 			expand.skip *= -1;
// 		if (input[i] == '$')
// 		{
// 				skip = advance_idx(&expand, input, i);
// 				if (skip == -1)
// 				{
// 					i++;
// 					continue ;
// 				}
// 				else
// 					i = skip;
// 				while (input[i] && (ft_isalnum(input[i]) || (input[i] == '_')))
// 					i++;
// 				to_replace_by = find_expand(glo, &input[expand.start], expand.start, i, expand.skip);
// 				line_negatif_expand(to_replace_by);
// 				if (input[i] == '?')
// 					i++;
// 				if (!to_replace_by)
// 					continue ;
// 				ft_strcat(expand.new_input, to_replace_by);
// 				j += ft_strlen(to_replace_by);
// 				continue ;
// 		}
// 		expand.new_input[j++] = input[i++];
// 	}
// 	free(input);
// 	return (expand.new_input);
// }

			// if (input[i] == '\'')
			// 	expand.skip *= -1;
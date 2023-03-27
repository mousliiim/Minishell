/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:40:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/27 23:10:34 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

static void	mini_itoa(t_global *glo)
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

char	*find_expand(t_global *glo, char *find, t_expand *exp)
{
	int	i;
	int	stop;

	i = 0;
	if (!ft_strncmp(find, "?", 1))
	{
		mini_itoa(glo);
		return (glo->str_status);
	}
	if (!(exp->i - exp->start))
	{
		if ((find[0] == '\'' || find[0] == '"') && exp->skip == 1)
			return (0);
		return ("$");
	}
	while (glo->personal_env.array[i])
	{
		stop = ft_strchr((char *)glo->personal_env.array[i], '=')
			- (char *)glo->personal_env.array[i];
		if (!ft_strncmp(find, (char *)glo->personal_env.array[i], stop)
			&& stop == exp->i - exp->start)
			return ((char *)(glo->personal_env.array[i] + stop + 1));
		i++;
	}
	return (0);
}

static void	ft_just_raft(char *new_input)
{
	if (check_first_char(new_input))
		ft_strcpy(new_input, new_input, 1);
}

char	*catch_expand(t_global *glo, char *input)
{
	int			tmp;
	size_t		len_to_malloc;
	char		*new_input;
	t_expand	exp;

	len_to_malloc = ft_strlen(input);
	ft_memset(&exp, 0, sizeof(exp));
	tmp = get_replacement_size(glo, &exp, input, len_to_malloc);
	if (tmp == -1)
		return (input);
	len_to_malloc = tmp;
	if (!len_to_malloc)
		return (input);
	new_input = ft_calloc(sizeof(char), len_to_malloc + 1);
	if (!new_input)
	{
		free_double_str((char **)glo->personal_env.array);
		ctrl_d(g_status);
		return (0);
	}
	ft_memset(&exp, 0, sizeof(exp));
	replace_variables(glo, &exp, input, new_input);
	free(input);
	ft_just_raft(new_input);
	return (new_input);
}

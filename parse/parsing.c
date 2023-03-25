/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:44:33 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/25 03:18:21 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;

int	ft_clean_quotes(char **line)
{
	int			ij[2];
	char		*tmp;
	char		delim;

	delim = 0;
	ij[0] = 0;
	ij[1] = 0;
	if (line == NULL || *line == NULL)
		return (0);
	tmp = malloc(sizeof(char) * (ft_strlen(*line) + 1));
	if (!tmp)
		return (0);
	while ((*line)[ij[0]])
	{
		if (((*line)[ij[0]] == '"' || (*line)[ij[0]] == '\'') && delim == 0)
			delim = (*line)[ij[0]++];
		else if ((*line)[ij[0]] == delim)
			ij[0]++;
		else
			tmp[ij[1]++] = (*line)[ij[0]++];
	}
	tmp[ij[1]] = '\0';
	free(*line);
	*line = tmp;
	return (1);
}

int	first_command(char **tab, char **arg, char *tmp, int *array[2])
{
	int	*i;
	int	*j;

	i = array[0];
	j = array[1];
	if (*i == 0 && !check_first_char(tab[0]))
	{
		tmp = ft_substr(tab[*i], 0, ft_strlen(tab[*i]));
		if (!tmp)
			return (0);
		ft_strjoin2(arg, tmp);
		if (!arg)
			return (0);
		free(tmp);
	}
	while (ft_isspace(tab[*i][*j]))
		(*j)++;
	return (1);
}

static int	cut_raft(char **res, char *line, int *array[5])
{
	int		*i;
	int		*j;
	int		*k;
	int		**flag;

	i = array[0];
	j = array[1];
	k = array[2];
	flag = (int *[2]){array[3], array[4]};
	while (line[*i + *flag[1]] == '>' || line[*i + *flag[1]] == '<')
		(*flag[1]) += 1;
	if (!*flag[0])
	{
		res[(*j)] = ft_substr(line, *k, *i - *k);
		if (!res[(*j)++])
			return (0);
	}
	else
		*flag[0] = 0;
	res[(*j)] = ft_substr(line, *i, *flag[1]);
	if (!res[(*j)++])
		return (0);
	*i += *flag[1] == 2;
	*k = *i + 1;
	return (1);
}

char	**ft_split_rafter(char *line)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	int		flg[2];

	i = -1;
	j = 0;
	k = 0;
	flg[0] = check_first_char(line) > 0;
	res = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!res)
		return (NULL);
	while (line[++i])
	{
		flg[1] = 0;
		if (line[i] == '>' || line[i] == '<')
			if (!cut_raft(res, line, (int *[5]){&i, &j, &k, &flg[0], &flg[1]}))
				return (ft_free(res, i), NULL);
	}
	res[j] = ft_substr(line, k, i - k);
	if (!res[j++])
		return (ft_free(res, j), NULL);
	res[j] = NULL;
	return (res);
}

void	catch_heredocs(t_global *glo, size_t nb_command)
{
	t_list_mini	*head;
	size_t		i;
	int			nb_hd;

	i = -1;
	nb_hd = 0;
	glo->here_doc_failed = 0;
	len_heredoc(glo, nb_command);
	while (++i < nb_command)
	{
		glo->struct_id[i].prev_heredocs = -1;
		head = glo->struct_id[i].head;
		while (head)
		{
			if (head->redirect == HERE_DOC && glo->here_doc_failed == 0)
			{
				nb_hd++;
				start_heredoc(glo, i, head, nb_hd);
			}
			head = head->next;
		}
	}
	if (glo->here_doc_failed == 1)
		close(glo->struct_id[0].prev_heredocs);
}

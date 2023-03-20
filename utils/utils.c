/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 05:34:48 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/19 22:05:00 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 7 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		if ((result * sign) > LLONG_MAX || (result * sign) < LLONG_MIN)
			exit(1);
		nptr++;
	}
	return (result * sign);
}

char	*ft_no_take_first_word(char *line)
{
	int		i;
	char	*res;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	res = ft_substr(line, 0, i);
	return (res);
}

void	*ft_realloc(void **old, size_t old_c, size_t new_c)
{
	void	**new;
	size_t	i;

	i = 0;
	new = ft_calloc(sizeof(void *), new_c);
	while (i < old_c)
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	return (new);
}

t_type	return_redir_enum(char *line)
{
	int		i;
	t_type	type;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '>' && line[i + 1] != '>')
		return (type = OUT);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (type = IN);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (type = HERE_DOC);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (type = APPEND);
	return (0);
}

char	*return_file_name(char *line)
{
	int		i;
	int		j;
	char	*file_name;

	i = 0;
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	file_name = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!file_name)
		return (NULL);
	while (line[i] != '\0' && line[i] != ' ')
	{
		file_name[j] = line[i];
		i++;
		j++;
	}
	file_name[j] = '\0';
	return (file_name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:51:58 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/10 04:31:07 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_tab_color(char **cmd)
{
	int		i;
	int		size;
	int		j;
	char	**new;

	i = 0;
	while (cmd[i])
		i++;
	size = i + 2;
	new = malloc(sizeof(char *) * size);
	i = 1;
	j = 2;
	new[1] = ft_strdup("--color");
	new[0] = ft_strdup("/usr/bin/ls");
	while (cmd[i])
	{
		new[j] = ft_strdup(cmd[i]);
		j++;
		i++;
	}
	new[j] = 0;
	return (new);
}

int	ls_color(t_global *glo, int j)
{
	int	forks;
	int	status;

	status = 0;
	glo->struct_id[j].split_command = \
		create_tab_color(glo->struct_id[j].split_command);
	if (glo->nb == 1)
	{
		forks = fork();
		if (forks == 0)
			execve(glo->struct_id[j].split_command[0],
				glo->struct_id[j].split_command,
				(char **)glo->personal_env.array);
		waitpid(forks, &status, 0);
	}
	else
		execve(glo->struct_id[j].split_command[0],
			glo->struct_id[j].split_command, (char **)glo->personal_env.array);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divided_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:21:23 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/21 20:41:36 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status;	

void error_msg(int err, char *cmd)
{
	if (err == 13)
		perror("miniboosted");
	else
		ft_printf("miniboosted: command not found : %s\n", cmd);
}

void	child_process(t_global *glo, t_builtins built_ptr, unsigned long i)
{
	signal(SIGINT, &ctrl_c);
	signal(SIGQUIT, &ctrl_antislash);
	if (i != 0)
		dupnclose(glo->prev, STDIN_FILENO);
	if (i != (glo->nb - 1))
		dup2(glo->link[1], STDOUT_FILENO);
	close(glo->link[0]);
	close(glo->link[1]);
	if (openfiles(glo, i) == -1)
	{
		free_inchild(glo);
		exit(1);
	}
	if (glo->struct_id[i].split_command && built_ptr)
	{
		built_ptr(glo, i);
		free_inchild(glo);
		exit(g_status);
	}
	if (!glo->struct_id[i].split_command || !glo->struct_id[i].split_command[0])
	{
		if (!glo->struct_id[i].head)
			ft_printf("miniboosted: : command not found\n");
		free_inchild(glo);
		exit(1);
	}
	if (ft_strchr(glo->struct_id[i].split_command[0], '/'))
	{

		if (!access(glo->struct_id[i].split_command[0], F_OK | X_OK))
		{
			execve(glo->struct_id[i].split_command[0],
				glo->struct_id[i].split_command,
				(char **)glo->personal_env.array);
		}
	}
	error_msg(errno, glo->struct_id[i].split_command[0]);
	free_inchild(glo);
	exit(127);
}
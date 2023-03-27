/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:32:09 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/27 23:37:04 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define MAX_READ_SIZE 10

extern int	g_status;

static void	exec_cmd_git(t_prompt *prompt, char **cmd, int choice)
{
	close(prompt->link[0]);
	if (choice == 1)
	{
		dup2(prompt->link[1], STDOUT_FILENO);
		dupnclose(prompt->link[1], STDERR_FILENO);
	}
	else if (choice == 2)
	{
		dup2(prompt->prev, STDIN_FILENO);
		dupnclose(prompt->link[1], STDOUT_FILENO);
	}
	execve(cmd[0], (char **)cmd, NULL);
	exit(0);
}

static int	get_git_branch(void)
{
	t_prompt			prompt;
	int					res;
	static const char	*command1[3] = {"/usr/bin/git", "branch", 0};
	static const char	*command2[3] = {"/usr/bin/grep", "*", 0};

	pipe(prompt.link);
	prompt.forkstate = fork();
	if (prompt.forkstate == 0)
	{
		exec_cmd_git(&prompt, (char **)command1, 1);
	}
	wait(0);
	prompt.prev = prompt.link[0];
	close(prompt.link[1]);
	pipe(prompt.link);
	prompt.forkstate = fork();
	if (prompt.forkstate == 0)
	{
		exec_cmd_git(&prompt, (char **)command2, 2);
	}
	wait(0);
	close(prompt.link[1]);
	close(prompt.prev);
	res = prompt.link[0];
	return (res);
}

char	*build_prompt(int opt)
{
	char		buffer[MAX_READ_SIZE + 1];
	int			fd;
	size_t		red;
	static char	prompt[170];

	if (!opt)
		return ("$MiniBoosted : ");
	if (g_status == 0)
		ft_strcpy_maxou(prompt, GB ARROW EB RB "$MiniBoosted " EB);
	else
		ft_strcpy_maxou(prompt, RB ARROW EB RB "$MiniBoosted " EB);
	fd = get_git_branch();
	red = read(fd, buffer, 2);
	buffer[3] = 0;
	if (!red)
		return (close(fd), prompt);
	red = read(fd, buffer, MAX_READ_SIZE);
	close(fd);
	buffer[red - 1] = 0;
	ft_strcat(prompt, BB "git:(" EB);
	ft_strcat(prompt, RB);
	ft_strcat(prompt, buffer);
	ft_strcat(prompt, EB);
	ft_strcat(prompt, BB ") " EB);
	return (prompt);
}



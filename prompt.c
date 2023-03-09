/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:32:09 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/09 05:29:44 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

#define MAX_READ_SIZE 10

extern int	g_status;

char	*build_prompt(char *prompt)
{
	static const char	*arrows[3] = {GB "→  " EB CB "$MiniBoosted " EB, RB "→  " EB CB "$MiniBoosted " EB, BB "git:(" EB};
	char				buffer[MAX_READ_SIZE + 1];
	int					fd;
	size_t					red;
	int					i;
	
	(void) arrows[2];
	(void) i;
	if (g_status == 0)
		ft_strcpy_maxou(prompt, GB "→  " EB CB "$MiniBoosted " EB);
	else
		ft_strcpy_maxou(prompt, RB "→  " EB CB "$MiniBoosted " EB);
	fd = get_git_branch();
	red = read(fd, buffer, 2);
	buffer[3] = 0;
	if (!red)
		return (prompt);
	red = read(fd, buffer, MAX_READ_SIZE);
	close(fd);
	buffer[red - 1] = 0;
	ft_strcat(prompt, (char *)arrows[2]);
	ft_strcat(prompt, RB);
	ft_strcat(prompt, buffer);
	ft_strcat(prompt, EB);
	ft_strcat(prompt, BB ") " EB );
	return (prompt);
}

int	get_git_branch(void)
{
	int					forkstate;
	int					prev;
	int					res;
	static const char	*command1[3] = {"/usr/bin/git", "branch", 0};
	static const char	*command2[3] = {"/usr/bin/grep", "*", 0};
	static const char	*env[1] = {0};
	int					link[2];

	pipe(link);
	forkstate = fork();
	if (forkstate == 0)
	{
		close(link[0]);
		dup2(link[1], STDOUT_FILENO);
		dup2(link[1], STDERR_FILENO);
		close(link[1]);
		execve(command1[0], (char **)command1, (char **)env);
		exit(0);
	}
	else
	{
		wait(0);
		prev = link[0];
		close(link[1]);
	}
	pipe(link);
	forkstate = fork();
	if (forkstate == 0)
	{
		dup2(prev, STDIN_FILENO);
		dup2(link[1], STDOUT_FILENO);
		close(link[1]);
		close(link[0]);
		execve(command2[0], (char **)command2, (char **)env);
	}
	close(link[1]);
	close(prev);
	res = link[0];
	// close(link[0]);
	return (res);
}

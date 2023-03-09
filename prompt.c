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

extern int	g_status;

char	*build_prompt(void)
{
	static const char	*arrows[3] = {GB "→  " EB CB "$MiniBoosted " EB, RB "→  " EB CB "$MiniBoosted " EB, BB "git:(" EB};
	// char				*branch;
	// int					i;
	// size_t				branch_size;
	char				*prompt;

	(void) arrows[2];
	if (g_status == 0)
		prompt = GB "→  " EB CB "$MiniBoosted " EB BRB "✗ " EB;
	else
		prompt = RB "→  " EB CB "$MiniBoosted " EB BRB "✗ " EB;
	// fprintf(stderr, "prpompt >> %s\n", arrows[1]);
	// printf("%s", arrows[2]);
	return (prompt);
	// branch = get_git_branch();
	// i = 0;
	// if (branch)
	// {
	// 	branch_size = ft_strlen(branch);
	// 	if (branch_size > 42)
	// 		return (prompt);
	// 	prompt = malloc (sizeof(ft_strlen(prompt) + 20 + branch_size + 1));
	// 	prompt = ft_strlcat(prompt, arrows[0], ft_strlen(arrows[2]));
	// 	// prompt = ft_strlcat();
	// 	return (prompt);
	// }
	// else
	// 	return (prompt);
	// free(branch);
}

char	*get_git_branch(void)
{
	int					forkstate;
	int					prev;
	char				*res;
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
	res = get_next_line(link[0]);
	close(link[0]);
	return (res);
}

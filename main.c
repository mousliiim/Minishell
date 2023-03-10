/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/14 22:46:43 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_status;

static int	syntax_checker(char *line)
{
	line_negatif(line);
	if (!quote_checker(line))
	{
		ft_printf("Syntax error : quote not closed\n");
		return (0);
	}
	if (!rafter_checker(line))
	{
		ft_printf("bash: syntax error near unexpected token 'newline'\n");
		return (0);
	}
	if (!pipe_checker(line))
	{
		ft_printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

static void	init_shell(t_global *global, char **env)
{
	global->status = 0;
	g_status = 0;
	signal(SIGINT, &ctrl_c);
	global->personal_env = build_personal_env(env);
	signal(SIGQUIT, SIG_IGN);
}

static int	loop_shell(t_global *global, char *input)
{
	t_split_line	splitted_line;
	t_tab_struct	*tab_struct;

	add_history(input);
	if (!syntax_checker(input))
	{
		free(input);
		return (-42);
	}
	input = catch_expand(global, input);
	splitted_line = split_line(input);
	tab_struct = ft_calloc(sizeof(t_tab_struct), splitted_line.strings.size);
	if (!tab_struct)
		return (0);
	split_input(splitted_line, tab_struct);
	global->struct_id = tab_struct;
	global->nb = splitted_line.strings.size;
	global->path = set_path(global);
	catch_heredocs(global, global->nb);
	global->status = g_status;
	free_splitted_line(&splitted_line);
	go_exec(global);
	free(input);
	clear_lst(tab_struct, global->nb);
	size_t i = -1;
	while (++i < global->nb)
		free_double_str(tab_struct[i].split_command);
	free(tab_struct);
	free_double_str(global->path);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char			*input;
	t_global		global;

	if (ac != 1 || av[1])
		return (0);
	init_shell(&global, env);
	endton(&global);
	while (TRUE)
	{
		input = readline(build_prompt());
		if (!input)
			ctrl_d(g_status);
		if (!*input)
			continue ;
		if (loop_shell(&global, input) == -42)
			continue ;
	}
	free_double_str((char **)global.personal_env.array);
}

// $'$USER'p$LESS ls
// miniboosted: command not found : mparisse-R
// bash: $USERp-R: command not found


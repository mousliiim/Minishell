/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/22 05:50:36 by mmourdal         ###   ########.fr       */
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
	if (!global->personal_env.array)
	{
		ft_printf("Error: malloc failed\n");
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
}

static void	free_end_loop_shell(t_global *global, t_tab_struct *tab_struct, \
		size_t tempsize)
{
	size_t	i;

	clear_lst(tab_struct, tempsize);
	i = -1;
	while (++i < tempsize)
		free_double_str(tab_struct[i].split_command);
	i = -1;
	while (++i < tempsize)
		free_double_str(tab_struct[i].commands);
	free(tab_struct);
	free_double_str(global->path);
}

void	free_shell(t_global *global, char *input)
{
	free_double_str((char **)global->personal_env.array);
	free(input);
	ft_printf("Error: Allocation memory failed\n");
	ft_printf("exit\n");
	exit(1);
}

static int	loop_shell(t_global *global, char *input)
{
	t_split_line	splitted_line;
	t_tab_struct	*tab_struct;
	size_t			tempsize;

	add_history(input);
	if (!syntax_checker(input))
		return (-42);
	input = catch_expand(global, input);
	if (!input)
		free_shell(global, input);
	splitted_line = split_line(input);
	if (!splitted_line.strings.capacity)
		free_shell(global, input);
	tab_struct = ft_calloc(sizeof(t_tab_struct), splitted_line.strings.size);
	if (!tab_struct)
		return (0); // A FREE A LA PLACE
	if (!split_input(splitted_line, tab_struct))
		return (0); // A FREE A LA PLACE
	global->struct_id = tab_struct;
	global->nb = splitted_line.strings.size;
	global->path = set_path(global); // A FREE A LA PLACE
	global->status = g_status;
	free_splitted_line(&splitted_line);
	catch_heredocs(global, global->nb);
	tempsize = global->nb;
	free(input);
	if (global->here_doc_failed == 0)
		go_exec(global);
	free_end_loop_shell(global, tab_struct, tempsize);
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
		{
			free_double_str((char **)global.personal_env.array);
			ctrl_d(g_status);
		}
		if (!*input)
			continue ;
		if (loop_shell(&global, input) == -42)
		{
			free(input);
			g_status = 2;
			continue ;
		}
	}
}

// $'$USER'p$LESS ls
// miniboosted: command not found : mparisse-R
// bash: $USERp-R: command not found
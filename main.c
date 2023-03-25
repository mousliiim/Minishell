/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/25 02:56:30 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_status;

static int	syntax_checker(char *line)
{
	line_negatif(line);
	if (!quote_checker(line))
	{
		ft_printf("MiniBoosted: quote not closed\n");
		return (0);
	}
	if (!rafter_checker(line))
	{
		ft_printf("MiniBoosted: syntax error near unexpected token 'newline'\n");
		return (0);
	}
	if (!pipe_checker(line))
	{
		ft_printf("MiniBoosted: syntax error near unexpected token `|'\n");
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
	endton(global);
}

void	free_end_loop_shell(t_global *global, t_tab_struct *tab_struct, \
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
		free_shell(global, input, 0);
	splitted_line = split_line(input);
	if (!splitted_line.strings.capacity)
		free_shell(global, input, 0);
	tab_struct = ft_calloc(sizeof(t_tab_struct), splitted_line.strings.size);
	if (!tab_struct)
		return (free_shell(global, input, 0), free_splitted_line(&splitted_line), 0);
	global->struct_id = tab_struct;
	if (!split_input(splitted_line, tab_struct))
		return (free_splitted_line(&splitted_line), free_shell(global, input, 1), 0);
	global->nb = splitted_line.strings.size;
	free_splitted_line(&splitted_line);
	free(input);
	global->path = set_path(global);
	global->status = g_status;
	catch_heredocs(global, global->nb);
	tempsize = global->nb;
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
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	init_shell(&global, env);
	while (TRUE)
	{
		input = readline(build_prompt());
		if (!input)
		{
			free_double_str((char **)global.personal_env.array);
			ctrl_d(g_status);
		}
		else if (!*input)
			continue ;
		if (loop_shell(&global, input) == -42)
		{
			free(input);
			g_status = 2;
		}
	}
}

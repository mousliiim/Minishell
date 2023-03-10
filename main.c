/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/10 06:42:11 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_status;

t_split_line	split_line(const char *line)
{
	t_split_line	res;
	int				i;
	char			*tmp;
	int				start;

	res.strings = pa_new();
	i = 0;
	while (1)
	{
		while (ft_isspace(line[i]))
			i++;
		start = i;
		while ((line[i] && line[i] != '|'))
			i++;
		if (i > start)
		{
			tmp = ft_substr(line, start, i - start);
			pa_add(&res.strings, tmp);
		}
		if (!line[i])
			break ;
		i++;
	}
	return (res);
}

int	syntax_checker(char *line)
{
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

int		main(int ac, char **av, char **env)
{
	char				*input;
	static t_tab_struct	*tab_struct;
	static t_global		global;
	t_split_line		splitted_line;
	int					i;
	int					j;
	size_t				global_tmp_nb;
	char *file_name;
	t_type type;
	size_t				k;

	if (ac != 1 || av[1])
		return (0);
	global.status = 0;
	g_status = 0;
	signal(SIGINT, &ctrlc);
	global.personal_env = build_personal_env(env);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		input = readline(build_prompt());
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (!*input)
			continue ;
		add_history(input);
		// catch_expand(input);
		line_negatif(input);
		if (!syntax_checker(input))
		{
			free(input);
			continue ;
		}
		splitted_line = split_line(input);
		i = splitted_line.strings.size;
		j = 0;
		while (j < i)
		{
			if (!syntax_checker(splitted_line.strings.array[j]))
			{
				i = -42;
				break ;
			}
			j++;
		}
		if (i == -42)
		{
			free_splitted_line(&splitted_line);
			continue ;
		}
		if (splitted_line.strings.size == 0)
		{
			free_splitted_line(&splitted_line);
			continue ;
		}
		ft_clean_quotes((char **)splitted_line.strings.array);
		tab_struct = ft_calloc(sizeof(t_tab_struct),
				splitted_line.strings.size);
		if (!tab_struct)
			return (0);
		global.struct_id = tab_struct;
		global.nb = splitted_line.strings.size;
		global_tmp_nb = splitted_line.strings.size;
		i = splitted_line.strings.size;
		j = 0;
		while (j < i)
		{
			if (rafter_line(splitted_line.strings.array[j]))
			{
				tab_struct[j].split_command = ft_have_two_word(ft_split_rafter(splitted_line.strings.array[j]));
				tab_struct[j].commands = ft_split_rafter(splitted_line.strings.array[j]);
				if (tab_struct[j].split_command
					&& check_first_char(tab_struct[j].commands[0]))
				{
					tab_struct[j].commands = ft_split_rafter(splitted_line.strings.array[j]);
					k = 0;
					while (tab_struct[j].commands[k])
					{
						tab_struct[j].commands[k] = ft_no_take_first_word(return_file_name(tab_struct[j].commands[k]));
						k++;
					}
					k = 0;
					while (tab_struct[j].commands[k])
					{
						file_name = return_file_name(tab_struct[j].commands[k
								+ 1]);
						type = return_redir_enum(tab_struct[j].commands[k]);
						ft_lstadde_back(&tab_struct[j].head,
								ft_lstnewe(file_name, type));
						k += 2;
					}
				}
				else if (tab_struct[j].split_command
						&& !check_first_char(tab_struct[j].commands[0]))
				{
					tab_struct[j].commands = ft_split_rafter(splitted_line.strings.array[j]);
					k = 0;
					while (tab_struct[j].commands[k])
					{
						tab_struct[j].commands[k] = ft_no_take_first_word(return_file_name(tab_struct[j].commands[k]));
						k++;
					}
					k = 1;
					while (tab_struct[j].commands[k])
					{
						file_name = return_file_name(tab_struct[j].commands[k
								+ 1]);
						type = return_redir_enum(tab_struct[j].commands[k]);
						ft_lstadde_back(&tab_struct[j].head,
								ft_lstnewe(file_name, type));
						k += 2;
					}
				}
				else if (tab_struct[j].split_command == NULL)
				{
					k = 0;
					while (tab_struct[j].commands[k])
					{
						file_name = return_file_name(tab_struct[j].commands[k
								+ 1]);
						type = return_redir_enum(tab_struct[j].commands[k]);
						ft_lstadde_back(&tab_struct[j].head,
								ft_lstnewe(file_name, type));
						k += 2;
					}
				}
			}
			else
				tab_struct[j].split_command = ft_split(splitted_line.strings.array[j],
						' ');
			if (tab_struct[j].split_command)
			{
				k = 0;
				while (tab_struct[j].split_command[k])
				{
					line_positif(tab_struct[j].split_command[k]);
					k++;
				}
			}
			if (tab_struct[j].commands)
			{
				k = 0;
				while (tab_struct[j].commands[k])
				{
					line_positif(tab_struct[j].commands[k]);
					k++;
				}
			}
			j++;
		}
		global.path = set_path(&global);
		catch_heredocs(&global, global_tmp_nb);
		global.status = g_status;
		go_exec(&global);
		k = 0;
		while (k < global_tmp_nb)
		{
			ft_lstcleare(&tab_struct[k].head, free);
			k++;
		}
		free_splitted_line(&splitted_line);
		// for (int k = 0; k < i; k++)
		// 	free_double_str(tab_struct[k].split_command);
		free(tab_struct);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/11 23:05:37 by mmourdal         ###   ########.fr       */
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

char	*getter(char *env_var)
{
	int	stop;

	stop = ft_strchr(env_var, '=') - env_var;
	return (&env_var[stop + 1]);
}

char	*find_expand(t_global *glo, char *find, int start, int end)
{
	int		i;
	int		stop;

	i = 0;
	if (end - start == 0)
		return("$");
	if (!ft_strcmp(find ,"?"))
		return (ft_itoa(g_status));
	while (glo->personal_env.array[i])
	{
		if (!ft_strncmp((char *)glo->personal_env.array[i], find, end - start))
		{
			stop = ft_strchr((char *)glo->personal_env.array[i], '=') - (char *)glo->personal_env.array[i];
			return ((char *)&glo->personal_env.array[i][stop + 1]);
		}
		i++;
	}
	return (0);
}

char	*catch_expand(t_global *glo, char *input)
{
	int		i;
	int		j;
	int		start;
	char	*to_replace_by;
	size_t	len_to_malloc;
	char	*new_input;

	i = 0;
	to_replace_by = 0;
	start = 0;
	len_to_malloc = ft_strlen(input);
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '$')
				i++;
			to_replace_by = find_expand(glo, &input[start], start, i);
			if (!to_replace_by)
				continue ;
			len_to_malloc += ft_strlen(to_replace_by);
			len_to_malloc -= i - start;
			continue ;
		}
		i++;
	}
	if (!start)
		return (input);
	new_input = malloc(sizeof(char) * len_to_malloc);
	j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '$')
			{
				i++;
			}
			to_replace_by = find_expand(glo, &input[start], start, i);
			if (!to_replace_by)
				continue ;
			ft_strcat(new_input, to_replace_by);
			j += ft_strlen(to_replace_by);
			continue ;
		}
		new_input[j] = input[i];
		j++;
		i++;
	}
	// fprintf(stderr, "here >> %s\n", new_input);
	return (new_input);
}

int	have_expand(char *str)
{
	int		expand;
	size_t	i;

	expand = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char				*input;
	static t_tab_struct	*tab_struct;
	static t_global		global;
	t_split_line		splitted_line;
	int					i;
	int					j;
	size_t				k;
	size_t				global_tmp_nb;

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
			input = NULL;
			break ;
		}
		if (!*input)
			continue ;
		add_history(input);
		line_negatif(input);
		if (have_expand(input))
			input = catch_expand(&global, input);
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
				break ;
			j++;
		}
		if (i != j)
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
				rafter_cut(&tab_struct[j], splitted_line, j);
			else
				tab_struct[j].split_command = ft_split(splitted_line.strings.array[j], ' ');
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
		free(input);
		k = 0;
		while (k < global_tmp_nb)
		{
			ft_lstcleare(&tab_struct[k].head, free);
			k++;
		}
		free_splitted_line(&splitted_line);
		free(tab_struct);
	}
}

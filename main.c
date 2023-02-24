/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/24 19:45:36 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	parse(char *str)
{
	int	i;
	int	different_command;

	i = 0;
	if (str[0] == 0)
		return (0);
	different_command = 1;
	while (str[i])
	{
		if (str[i] == '|')
			different_command++;
		i++;
	}
	return (different_command);
}

t_split_line	split_line(const char *line)
{
	t_split_line	res;
	int				i;
	int				start;

	res.strings = pa_new();
	i = 0;
	while (1)
	{
		while (ft_isspace(line[i]))
			i++;
		start = i;
		while (line[i] && line[i] != '|')
			i++;
		if (i > start)
			pa_add(&res.strings, ft_substr(line, start, i - start));
		if (!line[i])
			break ;
		i++;
	}
	return (res);
}

int	print_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (ft_printf("there is no env\n"), 0);
	
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

// 
char	**set_path(t_global *global)
{
	int		i;
	char	**path;

	i = 0;
	if (!global->env)
		return (0);
	else
	{
		while (global->env[i])
		{
			if (ft_strnstr(global->env[i], "PATH=", 5))
			{
				path = ft_split(global->env[i] + 5, ':');
				if (!path || !*path)
					return (0);
				return (path);
			}
			i++;
		}
	}
	return (0);
}

void	print_global(t_global *global)
{
	int	i;
	
	i = 0;
	print_env(global->path);
	while (i < global->nb)
	{
		printf("global->commands[i] >> %s\n", global->struct_id[i].commands);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int					nb_of_cmd;
	char				*input;
	static	t_tab_struct	*tab_struct;
	static	t_global global;
	t_split_line		splitted_line;

	if (ac != 1)
		return (0);
	while (42)
	{
		input = readline("$miniboosted: ");
		nb_of_cmd = parse(input);
		tab_struct = malloc(sizeof(t_tab_struct) * nb_of_cmd);
		splitted_line = split_line(input);
		printf("nb_of_cmd >> %d\n", nb_of_cmd);
		global.nb = nb_of_cmd;
		while (nb_of_cmd--)
		{
			tab_struct[nb_of_cmd].id = nb_of_cmd;
			tab_struct[nb_of_cmd].commands = splitted_line.strings.array[nb_of_cmd];
			printf("tab_struct[%d] >> %s\n", nb_of_cmd, (char *)tab_struct[nb_of_cmd].commands);
		}
		global.env = env;
		global.struct_id = tab_struct;
		global.path = set_path(&global);
		print_global(&global);
	}
}
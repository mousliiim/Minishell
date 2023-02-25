/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/25 03:31:48 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A FAIRE :
// char **commands for ls -l -a ls is [0] -l is [1] -a is [2]
// gerer les pipes si elle sont vide a gauche ou a droite genre | | | ou ||| ou || || ||
// MAXOU C FAIT SA GRACE A DISPLAY_SPLIT TU PEU VISUALISER BIEN REGARDE

int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
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
		while ((line[i] && line[i] != '|'))
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

// void	print_global(t_global *global)
// {
// 	// int	i;

// 	// i = 0;
// 	// print_env(global->path);
// 	// print_env(global->env);
// 	// while (i < global->nb)
// 	// {
// 		printf("global->commands[0] >> %s\n", global->struct_id[0].commands[0]);
// 		// printf("global->commands[0] >> %s\n", global->struct_id[0].commands[1]);
// 		// printf("global->commands[0] >> %s\n", global->struct_id[0].commands[2]);
// 		// printf("global->commands[0] >> %s\n", global->struct_id[0].commands[2]);
// 		// printf("global->commands[1] >> %s\n", global->struct_id[1].commands[0]);
// 		// printf("global->commands[1] >> %s\n", global->struct_id[0].commands[1]);
// 		// printf("global->commands[1] >> %s\n", global->struct_id[0].commands[2]);
// 		// i++;
// 	// }
// }

// int	find_path(t_command *command, char *av)
// {
// 	int		i;
// 	char	*command_w_path;

// 	i = -1;
// 	if (!command->absolute_command[0])
// 		return (0);
// 	if (ft_strchr(command->absolute_command[0], '/')
// 		&& access(command->absolute_command[0], F_OK | X_OK) == 0)
// 		return (1);
// 	if (errno == 13)
// 		return (ft_printf("pipex: %s: Permission denied\n", av), 0);
// 	while (command->path[++i])
// 	{
// 		command_w_path = ft_sup_strjoin(command->path[i], '/',
// 				command->absolute_command[0]);
// 		if (!command_w_path)
// 			return (free_and_exit(command), 0);
// 		if (access(command_w_path, F_OK | X_OK) != -1)
// 		{
// 			free(command->absolute_command[0]);
// 			return (command->absolute_command[0] = command_w_path, 1);
// 		}
// 		free(command_w_path);
// 	}
// 	return (0);
// }

// int	find_path_for_each_command(t_global *global)
// {
// 	int	i;
// 	char	*command_w_path;
	
// 	i = -1;
	
// 	while ()
// 	{
// 		;
// 	}
// }

void display_split(t_tab_struct *tab_struct)
{
	int i;
	int j;

	i = 0;
	while (i < tab_struct->nb_cmd)
	{
		j = 0;
		while (tab_struct[i].split_command[j])
		{
			if (j == 0)
				ft_printf("CMD = %s\nARGS = ", tab_struct[i].split_command[j]);
			else
				ft_printf("%s ", tab_struct[i].split_command[j]);
			j++;
		}
		write(1, "\n", 1);
	i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char				*input;
	static	t_tab_struct	*tab_struct;
	static	t_global global;
	t_split_line		splitted_line;
	int i;
	int j;

	if (ac != 1)
		return (0);
	while (42)
	{
		input = readline(GB"→  "EB BB"$Mini"EB WB"Boos"EB RB"ted: "EB);
		splitted_line = split_line(input);
		tab_struct = malloc(sizeof(t_tab_struct) * splitted_line.strings.size);
		global.nb = splitted_line.strings.size;
		global.env = env;
		global.struct_id = tab_struct;
		global.path = set_path(&global);
		tab_struct->nb_cmd = splitted_line.strings.size;
		i = splitted_line.strings.size;
		printf("Number of command = %ld\n", splitted_line.strings.size);
		j = 0;
		while (j < i)
		{
			tab_struct[j].id = j;
			tab_struct[j].commands = splitted_line.strings.array[j];
			tab_struct[j].split_command = ft_split((char *)tab_struct[j].commands, ' ');
			j++;
		}
		display_split(tab_struct);
		// print_global(&global);
	}
}

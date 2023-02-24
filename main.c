/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/24 01:59:15 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ptr_array.h"

int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

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
/*
je vais avoir 

shell : ls | cmd1 -arg |

// export later : where will set path
// multy pipe
*/
/*
0 echo 
1 cd absolu ou relatif
2 pwd
3 export
4 unset
5 env
6 exit

un tableau de structure -> la structure split_line
je suis suppose faire un une fonction export qui est extensible
cette maniere

ou

trouver un moyen de rendre extensible de agrandir une structure
en fonction du nombre de pipe
*/
// int	check_exec_builtin(t_split_line *arg, t_global	)
// {
// 	int		i;
// 	static const char	*builtins[7] = {"echo","cd" ,"pwd", "export", "unset",
			// "env", "exit"};
// 	long int	*func[7] = {&echo, &cd , &pwd, &export, &unset, &env, &exit};

// 	i = 0;
// 	while (builtins[i])
// 	{
// 		if (!ft_strcmp(builtins[i], arg->array[0]))

// 	}
// }

int	parse(char *str)
{
	int	i;
	int	different_command;

	i = 0;
	different_command = 1;
	while (str[i])
	{
		if (str[i] == '|')
			different_command++;
		i++;
	}
	return (different_command);
}

t_split_line	split_line(const char *line, int stop)
{
	t_split_line	res;
	int				i;
	int				start;

	res.strings = pa_new();
	i = 0;
	while (1)
	{
		while (ft_isspace(line[i]) && i < stop)
			i++;
		if (line[i] == 0 || i == stop)
			break ;
		start = i;
		while (ft_isspace(line[i]) == 0 && line[i] && i < stop)
			i++;
		pa_add(&res.strings, ft_strndup(&line[start], i - start));
	}
	return (res);
}

void	print_my_commands(int nb, void **cmds)
{
	int	i;
	int	j;
	t_split_line	*ptr;

	j = 0;
	while (j < nb)
	{
		i = 0;
		ptr = cmds[j];
		while (i < ptr->strings.size)
		{
			printf("command[%d] >> %s\n", i,
					(char *)ptr->strings.array[i]);
			i++;
		}
		j++;
	}
}	

int	main(int ac, char **av, char **env)
{
	int nb_of_cmd;
	char *input;
	t_split_line splitted_line;

	(void)splitted_line;
	(void)nb_of_cmd;
	if (ac != 1)
		return (0);
	// i need to set path here
	while (1737)
	{
		input = readline("$minibooster: ");
		nb_of_cmd = parse(input);
		// commands = tabs_of_struct(input, nb_of_cmd);
		splitted_line = split_line(input, 42);
		printf("there is %d different command\n", nb_of_cmd);
		// print_my_commands(nb_of_cmd, commands);
		// i need to malloc a tab of structure times the number of command

		// free splitted line
	}
}
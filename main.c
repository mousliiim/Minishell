/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/27 18:08:39 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A FAIRE :
// JM MA TROUVER SA COMME ERREUR DANS LA SYNTAXE :
// →  $MiniBoosted ✗ < d> a>>d
// →  $MiniBoosted ✗ < d> >>d
// →  $MiniBoosted ✗ < d> >>d
// →  $MiniBoosted ✗ < d> >a
// →  $MiniBoosted ✗ < d> >d

// RECONSTRUIRE L'ENV !

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
			// free(tmp);
		}
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

void	display_split(t_tab_struct *tab_struct, t_global *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->nb)
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

void	waiting(int *forkstates, int size_wait)
{
	int	i;
	int	status;
	int	exit_code;
	int	signal_code;

	i = 0;
	status = 0;
	exit_code = 0;
	signal_code = 0;
	// ft_printf("il y a %d processus a attendre\n", size_wait);
	while (i < size_wait)
	{
		// ft_printf("le processus a attendre est %d\n", forkstates[i]);
		waitpid(forkstates[i], &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				exit_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != 0)
				signal_code = WTERMSIG(status);
		}
		i++;
	}
	(void)signal_code;
	(void)exit_code;
	//free resources
	// if (exit_code != 0)
	// 	exit(exit_code);
	// else
	// 	exit(signal_code);
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
	// line_negatif(line);
	// printf("line negatif = %s\n", line);
	// line_positif(line);
	// printf("line positif = %s\n", line);
	return (1);
}

void	free_double_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_splitted_line(t_split_line *del)
{
	size_t	size;
	int		i;

	i = 0;
	size = pa_size(&del->strings);
	while (i < size)
	{
		free(pa_get(&del->strings, i));
		i++;
	}
	pa_delete(&del->strings);
}

t_ptr_array	build_personal_env(char **env)
{
	int			i;
	t_ptr_array	res;

	i = 0;
	res = pa_new();
	while (env[i])
	{
		// printf("env[i] >> %s \n", env[i]);
		pa_add(&res, env[i]);
		i++;
	}
	return (res);
}

int	main(int ac, char **av, char **env)
{
	char				*input;
	static t_tab_struct	*tab_struct;
	static t_global		global;
	t_split_line		splitted_line;
	int					i;
	int					j;

	if (ac != 1)
		return (0);
	global.env = env;
	global.personal_env = build_personal_env(env);
	global.path = set_path(&global);
	while (42)
	{
		input = readline(GB "→  " EB CB "$MiniBoosted " BRB "✗ " EB);
		if (!input)
			break ;
		if (!*input)
			continue ;
		add_history(input);
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
		tab_struct = malloc(sizeof(t_tab_struct) * splitted_line.strings.size);
		global.nb = splitted_line.strings.size;
		global.struct_id = tab_struct;
		global.nb = splitted_line.strings.size;
		i = splitted_line.strings.size;
		j = 0;
		while (j < i)
		{
			tab_struct[j].id = j;
			tab_struct[j].commands = splitted_line.strings.array[j];
			tab_struct[j].split_command = ft_split((char *)tab_struct[j].commands,
													' ');
			j++;
		}
		// display_split(tab_struct,&global);
		free_splitted_line(&splitted_line);
		go_exec(&global);
		for (int k = 0; k < i; k++)
			free_double_str(tab_struct[k].split_command);
		free(tab_struct);
	}
	free_double_str(global.path);
}

/*
Erreur de syntaxe:
// typedef struct token{
// 	char *token
// 	int type;
// 	struct token *next;
// }


// [{ls}, {b}, {-la}]
// // enum{
// // 	redir = 0;
// // 	commande = 1;
// // }


// // typedef struct command{
// // 	
// // 	token *token;
// // }



// // typedef struct token{
// // 	char *token
// // 	int type;
// // 	struct token *next;
// // }
*/
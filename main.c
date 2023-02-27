/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/27 04:08:55 by mmourdal         ###   ########.fr       */
=======
/*   Updated: 2023/02/27 02:39:28 by mparisse         ###   ########.fr       */
>>>>>>> maxou
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A FAIRE :
// char **commands for ls -l -a ls is [0] -l is [1] -a is [2]
// gerer les pipes si elle sont vide a gauche ou a droite genre | | | ou ||| ou
// || || ||
// MAXOU C FAIT SA GRACE A DISPLAY_SPLIT TU PEU VISUALISER BIEN REGARDE

// Bah ecoute moi aussi ca avance de mon cote les pipes marchent j'ai l'impression
// que tout est carre de ce cote la
// next -> redirection

// note il faut que on essaie de garder dans le main.c
// toutes les fonctions qui l'on appelle dans le main

// test a reverifirer pour l'exec
// cat | cat | ls
// cat | ls
// ls | cat

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

int	quote_checker(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 1;
	while (line[i])
	{
		if (line[i] == '"' && double_quote == 1 && single_quote == 0)
			double_quote = 0;
		else if (line[i] == '"' && double_quote == 0 && single_quote == 0)
			double_quote = 1;
		else if (line[i] == '\'' && double_quote == 1 && single_quote == 0)
			single_quote = 1;
		else if (line[i] == '\'' && double_quote == 1 && single_quote == 1)
			single_quote = 0;
		i++;
	}
	if (single_quote == double_quote)
		return (0);
	return (1);
}

int is_operator(char *c, int j)
{
	if (c[j] == '|' || c[j] == '<' || c[j] == '>' || (c[j] == '>' && c[j + 1] == '>') || (c[j] == '<' && c[j + 1] == '<'))
		return (1);
	return (0);
}

void line_negatif(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			j = i + 1;
			while (line[j] && (line[j] != '"' || line[j] == '\''))
			{
				if (line[j] == '"' || line[j] == '\'')
					break ;
				if (ft_isspace(line[j]) || is_operator(line, j))
					line[j] = line[j] * -1;
				j++;
			}
		}
		i++;
	}
}

void line_positif(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			j = i + 1;
			while (line[j] && (line[j] != '"' || line[j] == '\''))
			{
				if (line[j] == '"' || line[j] == '\'')
					break ;
				if (ft_isspace(line[j]) || is_operator(line, j))
					line[j] = line[j] * -1;
				j++;
			}
		}
		i++;
	}
}

int	rafter_checker(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	if ((ft_strlen(str) == 1 && (str[i] == '<' || str[i] == '>')) || ((ft_strlen(str) == 2 && (str[i] == '<' || str[i] == '>')) && (ft_isspace(str[i + 1]) && !str[i + 2])))
		return (0);
	if (ft_strlen(str) == 2 && ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')))
		return (0);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			j = i + 1;
			while (ft_isspace(str[j]))
				j++;
			while (str[j])
			{
				if ((str[j] == '<' || str[j] == '>') && !str[j + 1])
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
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
	global.path = set_path(&global);
	while (42)
	{
		input = readline(GB "→  " EB CB "$MiniBoosted " BRB "✗ " EB);
		if (!input)
			break ;
		if (!*input)
			continue ;
		if (!syntax_checker(input))
		{
<<<<<<< HEAD
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
				continue ;
			tab_struct = malloc(sizeof(t_tab_struct)
					* splitted_line.strings.size);
			global.nb = splitted_line.strings.size;
			global.env = env;
			global.struct_id = tab_struct;
			global.path = set_path(&global);
			global.nb = splitted_line.strings.size;
			i = splitted_line.strings.size;
			j = 0;
			while (j < i)
			{
				fprintf(stderr, "%s \n",
						(char *)splitted_line.strings.array[j]);
				tab_struct[j].id = j;
				tab_struct[j].commands = splitted_line.strings.array[j];
				tab_struct[j].split_command = ft_split((char *)tab_struct[j].commands,
														' ');
				j++;
			}
			pa_delete(&splitted_line.strings);
			go_exec(&global);
			// free_double_str(tab_struct[0].split_command);
			free(tab_struct);
			// pa_delete(tab_struct[0].commands.strings.array[0]);
			// waiting(global.forkstates, global.nb);
			// display_split(tab_struct);
=======
			ft_printf("Syntax error : quote not closed\n");
			continue ;
>>>>>>> maxou
		}
		splitted_line = split_line(input);
		add_history(input);
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
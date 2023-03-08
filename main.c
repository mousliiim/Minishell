/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:47:32 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/08 06:59:13 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**set_path(t_global *global)
{
	int		i;
	char	**path;

	i = 0;
	if (global->personal_env.size == 0)
		return (0);
	else
	{
		while (i < global->personal_env.size) //(global->env[i])
		{
			if (ft_strnstr((char *)global->personal_env.array[i], "PATH=", 5))
			{
				path = ft_split((char *)global->personal_env.array[i] + 5, ':');
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
			if (j == 0 || tab_struct[i].split_command[j][0] == '<'
				|| tab_struct[i].split_command[j][0] == '>')
				ft_printf("CMD = %s\n", tab_struct[i].split_command[j]);
			else
				ft_printf("ARGS = %s\n", tab_struct[i].split_command[j]);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	waiting(t_global *global, int size_wait)
{
	int	i;
	int	exit_code;
	int	status;

	i = 0;
	status = 0;
	exit_code = 0;
	while (i < size_wait)
	{
		waitpid(global->forkstates[i], &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
		}
		i++;
	}
	global->status = exit_code;
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
		pa_add(&res, ft_strdup(env[i]));
		i++;
	}
	return (res);
}

void	print_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_printf("%s\n", str[i++]);
}
#include <signal.h>

void	ctrlc(int sig)
{
	fprintf(stderr, "Hhey maxou, un tout peu maximuuum\n");
}

int	rafter_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1] == '>')
			return (1);
		else if (line[i] == '>' && line[i + 1] != '>')
			return (1);
		else if (line[i] == '<' && line[i + 1] == '<')
			return (1);
		else if (line[i] == '<' && line[i + 1] != '<')
			return (1);
		i++;
	}
	return (0);
}

int	check_first_char(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '>' && line[i + 1] != '>')
		return (1);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (2);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (3);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (4);
	return (0);
}

char	*ft_no_take_first_word(char *line)
{
	int		i;
	char	*res;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	res = ft_substr(line, 0, i);
	return (res);
}

int	start_heredoc(t_global *glo, int j, t_list_mini *head)
{
	char	*str;
	int		link_heredoc[2];
	char	*limit;

	limit = head->file_name;
	pipe(link_heredoc);//check return value
	while (1)
	{
		str = readline("here_doc:");
		if (!str)
			break ;
		if (!ft_strcmp(str, limit))
		{
			break ;
		}
		ft_putendl_fd(str, link_heredoc[1]);
	}
	close(link_heredoc[1]);
	glo->struct_id[j].prev_heredocs = link_heredoc[0];
	return (0);
}

void	catch_heredocs(t_global *glo, size_t nb_command)
{
	t_list_mini	*head;
	int			i;

	i = 0;
	while (i < nb_command)
	{
		glo->struct_id[i].prev_heredocs = -1;
		head = glo->struct_id[i].head;
		while (head)
		{
			if (head->redirect == HERE_DOC)
			{
				start_heredoc(glo, i, head);
			}
			head = head->next;
			// if (head)
			// {
			// 	if (head->redirect == HERE_DOC)
			// 		close(glo->struct_id[i].prev_heredocs);
			// }
		}
		i++;
	}
}

int	ft_clean_quotes(char **line)
{
	int		i;
	int		j;
	int		k;
	int		delim;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	(void) k;
	if (line == NULL || *line == NULL)
		return (0);
	tmp = ft_strdup(*line);
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
		{
			delim = i;
			i++;
			while (tmp[i] != tmp[delim])
			{
				(*line)[j] = tmp[i];
				i++;
				j++;
			}
		}
		else
		{
			(*line)[j] = tmp[i];
			j++;
		}
		i++;
	}
	(*line)[j] = '\0';
	free(tmp);
	return (1);
}

// git branch 2> /dev/null
// sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'

char	*get_git_branch(t_global *global)
{
	int	forkstate;
	int prev;
	char *res;
	static const char	*command1[3] = {"/usr/bin/git", "branch", 0};
	static const char	*command2[3] = {"/usr/bin/grep", "*", 0};
	int	link[2];

	pipe(link);
	forkstate = fork();
	if (forkstate == 0)
	{
		close(link[0]);
		dup2(link[1], STDOUT_FILENO);
		dup2(link[1], STDERR_FILENO);
		close(link[1]);
		execve(command1[0], (char **)command1, (char **)global->personal_env.array);
		exit(0);
	}
	else
	{
		wait(0);
		prev = link[0];
		close(link[1]);
	}
	pipe(link);
	forkstate = fork();
	if (forkstate == 0)
	{
		dup2(prev, STDIN_FILENO);
		dup2(link[1], STDOUT_FILENO);
		close(link[1]);
		close(link[0]);
		execve(command2[0], (char **)command2, (char **)global->personal_env.array);
	}
	close(link[1]);
	close(prev);
	res = get_next_line(link[0]);
	close(link[0]);
	return (res);
}

int get_input(t_global *glo)
{
	static const char *arrows[4] = {GB "→  " EB, RB "→  " EB, RB "$MiniBoosted" EB, BB " git(" EB};
	char				*branch;
	int					i;
	
	if (glo->status == 0)
		printf("%s", arrows[0]);
	else
		printf("%s", arrows[1]);
	printf("%s", arrows[2]);
	branch = get_git_branch(glo);
	i = 0;
	if (branch)
	{
		printf("%s", arrows[3]);
		while(branch[i] && (branch[i] == '*' || branch[i] == ' '))
			i++;
		while(branch[i])
		{
			if (branch[i] == '\n')
			{
				i++;
				continue ;
			}
			printf(RB "%c", branch[i]);
			i++;
		}
		printf(EB BB ")" EB);
	}
	else
		return (1);
	return (1);
}

int	main(int ac, char **av, char **env)
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
	int					k;
	// char *output;

	if (ac != 1)
		return (0);
	global.status = 0;
	signal(SIGINT, &ctrlc);
	global.personal_env = build_personal_env(env);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		get_input(&global);
		if (global.status == 0)
			input = readline(" ");
		else
			input = readline(" ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		// catch expand
		add_history(input);
		// Faire ici une fonction qui va retirer du *char avant les quote et double quote pour passer
		// par la suite dans le syntax checker etc ...
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
		(void)global_tmp_nb;
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
					for (int k = 0; tab_struct[j].split_command[k]; k++)
						ft_printf("Cmd : %s\n", tab_struct[j].split_command[k]);
					for (int k = 0; tab_struct[j].commands[k]; k++)
						tab_struct[j].commands[k] = ft_no_take_first_word(return_file_name(tab_struct[j].commands[k]));
					for (int k = 0; tab_struct[j].commands[k]; k += 2)
					{
						file_name = return_file_name(tab_struct[j].commands[k
								+ 1]);
						type = return_redir_enum(tab_struct[j].commands[k]);
						ft_lstadde_back(&tab_struct[j].head,
								ft_lstnewe(file_name, type));
					}
				}
				else if (tab_struct[j].split_command
						&& !check_first_char(tab_struct[j].commands[0]))
				{
					tab_struct[j].commands = ft_split_rafter(splitted_line.strings.array[j]);
						// a voir ici
					for (int k = 0; tab_struct[j].split_command[k]; k++)
						ft_printf("Cmd : %s\n", tab_struct[j].split_command[k]);
					for (int k = 0; tab_struct[j].commands[k]; k++)
					{
						tab_struct[j].commands[k] = ft_no_take_first_word(return_file_name(tab_struct[j].commands[k]));
					}
					for (int k = 1; tab_struct[j].commands[k]; k += 2)
					{
						file_name = return_file_name(tab_struct[j].commands[k
								+ 1]);
						type = return_redir_enum(tab_struct[j].commands[k]);
						ft_lstadde_back(&tab_struct[j].head,
								ft_lstnewe(file_name, type));
					}
				}
				else if (tab_struct[j].split_command == NULL)
				{
					for (int k = 0; tab_struct[j].commands[k]; k += 2)
					{
						file_name = return_file_name(tab_struct[j].commands[k
								+ 1]);
						type = return_redir_enum(tab_struct[j].commands[k]);
						ft_lstadde_back(&tab_struct[j].head,
								ft_lstnewe(file_name, type));
					}
				}
			}
			else
			{
				tab_struct[j].split_command = ft_split(splitted_line.strings.array[j],
						' ');
			}
			if (tab_struct[j].split_command)
			{
				for (int k = 0; tab_struct[j].split_command[k]; k++)
				{
					line_positif(tab_struct[j].split_command[k]);
				}
			}
			if (tab_struct[j].commands)
			{
				for (int k = 0; tab_struct[j].commands[k]; k++)
					line_positif(tab_struct[j].commands[k]);
			}
			j++;
		}
		global.path = set_path(&global);
		catch_heredocs(&global, global_tmp_nb);
		go_exec(&global);
		// fprintf(stderr, "global->status >> %d\n", global.status);
		k = 0;
		while (k < global_tmp_nb)
		{
			// display(tab_struct[k].head);
			ft_lstcleare(&tab_struct[k].head, free);
			k++;
		}
		free_splitted_line(&splitted_line);
		// for (int k = 0; k < i; k++)
		// 	free_double_str(tab_struct[k].split_command);
		free(tab_struct);
	}
}

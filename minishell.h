/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:48:24 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/06 22:15:53 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <ctype.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# define BB "\001\033[1;34m\002"
# define CB "\001\033[1;36m\002"
# define WB "\001\033[1;37m\002"
# define RB "\001\033[1;31m\002"
# define GB "\001\033[1;32m\002"
# define BRB "\001\033[1;33m\002"
# define EB "\001\033[0m\002"

typedef struct s_ptr_array
{
	size_t	size;
	size_t	capacity;
	void	**array;
}	t_ptr_array;

typedef enum s_type
{
	IN = 1,
	OUT,
	APPEND,
	HERE_DOC
}	t_type;

typedef struct s_list_mini
{
	char				*file_name;
	t_type				redirect;
	struct s_list_mini	*next;
}	t_list_mini;

typedef struct s_tab_struct
{
	char			**commands;
	char			**split_command;
	int				type;
	t_list_mini		*head;
}	t_tab_struct;

typedef struct s_global
{
	char			**basic_env;
	t_tab_struct	*struct_id;
	t_ptr_array		personal_env;
	char			**path;
	int				*forkstates;
	int				status;
	int				link[2];
	int				prev;
	size_t			nb;
}	t_global;

typedef struct s_split_line
{
	t_ptr_array	strings;
	const char	*error_message;
	size_t		error_position;
}	t_split_line;

// pas encore utiliser 
typedef struct s_command_status
{
	bool	exit_shell;
	int		errnum;
}	t_command_status;

typedef int	(*builtins)(t_global *, int);

t_ptr_array		pa_new(void);
void			pa_pop(t_ptr_array	*array, size_t index);
void			pa_delete(t_ptr_array *pa);
void			pa_add(t_ptr_array *pa, void *ptr);
void			pa_pop_replace(t_ptr_array	*array, size_t index, void *new);
size_t			pa_size(t_ptr_array *pa);
void			*pa_get(t_ptr_array *pa, size_t index);
t_split_line	split_line(const char line[]);
int				ft_atoi(const char *nptr);
int				ft_isspace(char c);

/*********************** PARSING ***********************/
int				quote_checker(char *line);
int				is_operator(char *c, int j);
void			line_negatif(char *line);
void			line_positif(char *line);
int				rafter_checker(char *str);
int				rafter_check(char *str, int i, int *flag, int choice);
int				pipe_checker(char *line);
char			**ft_split_rafter(char *line);
size_t			ft_strlcpy2(char *dst, const char *src, size_t size);
char			**ft_have_two_word(char **tab);
int				check_first_char(char *line);
/******************************************************/

/*********************** RAFTER ***********************/
t_type			return_redir_enum(char *line);
char			*return_file_name(char *line);
t_list_mini		*ft_lstlaste(t_list_mini *lst);
t_list_mini		*ft_lstnewe(void *content, t_type type);
void			ft_lstadde_back(t_list_mini **lst, t_list_mini *new);
void			display(t_list_mini *head);
void			ft_lstcleare(t_list_mini **lst, void (*del)(void*));
/******************************************************/

/*********************** EXEC ***********************/
int				go_exec(t_global *global);
int				find_path_for_each_command(t_global *global);
int				forking(t_global *global, int i);
builtins	find_ptr_builtin(char *ptr);
void	waiting(t_global *global, int size_wait);
// void			waiting(int *forkstates, int size_wait);
/***************************************************/
int	echo(t_global *glo, int j);
/*********************** UTILS ***********************/
void			print_tab(char **str);
void			display_split(t_tab_struct *tab_struct, t_global *info);
/*****************************************************/


/*********************** UTILS ***********************/
int				cd(t_global *global, int i);
int				unset(t_global *glo, int j);
int				export(t_global *global, int j);
int				print_env(t_global *glo, int j);
int				pwd(t_global *glo, int j);
int				ls_color(t_global *glo, int j);
int				builtin_exit(t_global *global, int j);
/*****************************************************/

#endif
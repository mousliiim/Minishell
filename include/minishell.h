/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:48:24 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/10 06:41:47 by mmourdal         ###   ########.fr       */
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
# include <signal.h>
# include <limits.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# define BB "\001\033[1;34m\002"
# define CB "\001\033[1;36m\002"
# define WB "\001\033[1;37m\002"
# define RB "\001\033[1;31m\002"
# define GB "\001\033[1;32m\002"
# define BRB "\001\033[1;33m\002"
# define EB "\001\033[0m\002"
# define PATH_MAXIMUM        4096

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
	int				prev_heredocs;
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
	int				fd_solo_redirection;
	size_t			nb;
}	t_global;

typedef struct s_split_line
{
	t_ptr_array	strings;
	const char	*error_message;
	size_t		error_position;
}	t_split_line;

typedef int	(*t_builtins)(t_global *, int);

/********************* PTR_A_UTILS **********************/
t_ptr_array		pa_new(void);
void			pa_pop(t_ptr_array	*array, size_t index);
void			pa_delete(t_ptr_array *pa);
void			pa_pop_replace(t_ptr_array	*array, size_t index, void *new);
/********************************************************/

/****************** PTR_A_UTILS_SECOND *******************/
void			pa_add(t_ptr_array *pa, void *ptr);
size_t			pa_size(t_ptr_array *pa);
void			*pa_get(t_ptr_array *pa, size_t index);
/********************************************************/

t_split_line	split_line(const char line[]);
int				ft_atoi(const char *nptr);
int				ft_isspace(char c);

/******************* PATH_UTILS ************************/
char			**set_path(t_global *global);
t_ptr_array		build_personal_env(char **env);
int				find_path_for_each_command(t_global *global);
/******************************************************/

/******************* HERE_DOCS ************************/
int				start_heredoc(t_global *glo, int j, t_list_mini *head);
void			catch_heredocs(t_global *glo, size_t nb_command);
/******************************************************/

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
int				ft_clean_quotes(char **line);
/******************************************************/

/*********************** ENV **************************/
int				print_env(t_global *glo, int j);

/******************* /BUILTINS ************************/
char			**create_tab_color(char **cmd);
int				export(t_global *global, int j);
int				ls_color(t_global *glo, int j);
int				pwd(t_global *glo, int j);
int				builtin_exit(t_global *global, int j);
int				echo(t_global *glo, int j);
int				unset(t_global *glo, int j);
int				cd(t_global *global, int i);
/******************************************************/

/*********************** RAFTER ***********************/
int				rafter_line(char *line);
int				check_first_char(char *line);
/******************************************************/

/*********************** EXEC ***********************/
int				go_exec(t_global *global);
void			dupnclose(int fd1, int fd2);
int				forking(t_global *global, unsigned long i);
t_builtins		find_ptr_builtin(char *ptr);
int				openfiles_bt(t_global *glo, int j);
int				openfiles(t_global *glo, int j);
void			waiting(t_global *global, int size_wait);
/***************************************************/

/*********************** SIGNAL ***********************/
void			ctrlc(int sig);
/***************************************************/

/*********************** UTILS ***********************/
void			display_split(t_tab_struct *tab_struct, t_global *info);
char			*ft_no_take_first_word(char *line);
void			*ft_realloc(void **old, size_t old_c, size_t new_c);
t_type			return_redir_enum(char *line);
char			*return_file_name(char *line);
/*****************************************************/

/******************** LST_UTILS ********************/
t_list_mini		*ft_lstlaste(t_list_mini *lst);
t_list_mini		*ft_lstnewe(void *content, t_type type);
void			ft_lstadde_back(t_list_mini **lst, t_list_mini *new);
void			ft_lstcleare(t_list_mini **lst, void (*del)(void *));
/*****************************************************/

/****************** FREE_FUNCTION ********************/
void			free_splitted_line(t_split_line *del);
void			free_double_str(char **str);
/*****************************************************/

/********************* PROMPT ************************/
int				get_git_branch(void);
char			*build_prompt(char *prompt);
/*****************************************************/

/****************** TMP_UTILS ************************/
void			display_split(t_tab_struct *tab_struct, t_global *info);
void			print_tab(char **str);
void			display(t_list_mini *head);
/*****************************************************/

#endif
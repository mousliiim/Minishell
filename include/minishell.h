/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:48:24 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/26 03:07:01 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# define BB "\001\033[1;34m\002"
# define CB "\001\033[1;36m\002"
# define WB "\001\033[1;37m\002"
# define RB "\001\033[1;31m\002"
# define GB "\001\033[1;32m\002"
# define BRB "\001\033[1;33m\002"
# define EB "\001\033[0m\002"
# define ARROW "\001→ \002"
# define TRUE 1
# define PATH_MAXIMUM 4096

typedef struct s_ptr_array
{
	size_t				size;
	size_t				capacity;
	void				**array;
}						t_ptr_array;

typedef enum s_type
{
	IN = 1,
	OUT,
	APPEND,
	HERE_DOC
}						t_type;

typedef struct s_list_mini
{
	char				*file_name;
	t_type				redirect;
	struct s_list_mini	*next;
}						t_list_mini;

typedef struct s_tab_struct
{
	char				**commands;
	char				**split_command;
	int					type;
	int					prev_heredocs;
	t_list_mini			*head;
}						t_tab_struct;

typedef struct s_global
{
	char				**basic_env;
	t_tab_struct		*struct_id;
	t_ptr_array			personal_env;
	char				**path;
	char				str_status[3];
	int					*forkstates;
	int					status;
	int					link[2];
	int					prev;
	int					fd_solo_redirection;
	size_t				nb;
	size_t				nb_free;
	int					nb_hd;
	int					link_heredoc[2];
	int					here_doc_failed;
}						t_global;

typedef struct s_split_line
{
	t_ptr_array			strings;
}						t_split_line;

typedef struct s_airdock
{
	char				*str;
	int					forkstate;
}						t_airdock;

typedef struct s_prompt
{
	int					prev;
	int					res;
	int					link[2];
	int					forkstate;
}						t_prompt;

typedef int				(*t_builtins)(t_global *, int);

/********************* PARSE/PTR_A_UTILS **********************/
int						find_option(char **tab, char **arg, char *tmp,
							int *array[2]);
t_ptr_array				pa_new(void);
void					pa_pop(t_ptr_array *array, size_t index);
void					pa_delete(t_ptr_array *pa);
void					pa_pop_replace(t_ptr_array *array, size_t index,
							void *new);
/********************************************************/

/****************** PARSE/PTR_A_UTILS_SECOND *******************/
int						pa_add(t_ptr_array *pa, void *ptr);
size_t					pa_size(t_ptr_array *pa);
void					*pa_get(t_ptr_array *pa, size_t index);
void					before_exec_to_positif(t_tab_struct *tab_struct, int j);
/********************************************************/

/******************* ENV/PATH_UTILS ************************/
char					**set_path(t_global *global);
t_ptr_array				build_personal_env(char **env);
int						find_path_for_each_command(t_global *global);
/******************************************************/

/******************* EXEC/HERE_DOCS ************************/
t_global				*endton(t_global *glo);
int						start_heredoc(t_global *glo, int j, t_list_mini *head,
							int nbhd);
void					len_heredoc(t_global *glo, size_t nb_command);
/******************************************************/

/*********************** PARSING ***********************/
char					**ft_split_rafter(char *line);
int						first_command(char **tab, char **arg, char *tmp,
							int *array[2]);
size_t					ft_strlcpy2(char *dst, const char *src, size_t size);
char					**ft_have_two_word(char **tab, int j);
int						check_first_char(char *line);
void					catch_heredocs(t_global *glo, size_t nb_command);
int						ft_clean_quotes(char **line);
int						rafter_cut(t_tab_struct *tab_struct,
							t_split_line splitted_line, int j);
/******************************************************/

/******************* PARSE_CHECK ************************/
void					line_negatif(char *line);
int						quote_checker(char *line);
int						rafter_check(char *str, int i, int *flag, int choice);
int						rafter_checker(char *str);
int						pipe_checker(char *line);
/********************************************************/

/******************* EXPAND ********************/
void					mini_itoa(t_global *glo);
char					*catch_expand(t_global *glo, char *input);
char					*find_expand(t_global *glo, char *find, int start,
							int end, int skip);
/******************************************************/

/******************* PARSE/SPLIT_PARSING.c ********************/
int						split_input(t_split_line splitted_line,
							t_tab_struct *tab_struct);
t_split_line			split_line_c(char *s, int i, int go, t_split_line res);
t_split_line			split_line(char *line);
/******************************************************/

/*********************** ENV **************************/
int						print_env(t_global *glo, int j);

/******************* /BUILTINS ************************/
int						cd(t_global *global, int i);
int						echo(t_global *glo, int j);
int						builtin_exit(t_global *global, int j);
int						export(t_global *global, int j);
int						pwd(t_global *glo, int j);
int						unset(t_global *glo, int j);
/******************************************************/

/*********************** RAFTER ***********************/
int						rafter_line(char *line);
int						check_first_char(char *line);
/******************************************************/

/*********************** EXEC ***********************/
int						go_exec(t_global *global);
void					dupnclose(int fd1, int fd2);
int						forking(t_global *global, unsigned long i);
t_builtins				find_ptr_builtin(char *ptr);
void					waiting(t_global *global, int size_wait);
/***************************************************/

/*******************REDIRECTIONS*********************/
int						openfiles_bt(t_global *glo, int j);
int						openfiles(t_global *glo, int j);
/***************************************************/

/*******************DIVIDED_PROCESS*********************/
int						child_process(t_global *glo, t_builtins built_ptr,
							unsigned long i);
void					father_process(t_global *glo, unsigned long i);
void	builtin_solo_process(t_global *glo,
							t_builtins built_ptr,
							unsigned long i);
void					error_msg(int err, char *cmd);
/***************************************************/

/*********************** SIGNAL ***********************/
void					ctrl_antislash(int sig);
void					ctrl_c(int sig);
void					ctrl_d(int status);
void					quit_hd(int sign);
/***************************************************/

/*********************** UTILS ***********************/
int						syntax_checker(char *line);
char					*ft_no_take_first_word(char *line);
void					*ft_realloc(void **old, size_t old_c, size_t new_c);
t_type					return_redir_enum(char *line);
char					*return_file_name(char *line);
/*****************************************************/

/******************* UTILS_SECOND *********************/
char					*ft_strcpy(char *dest, const char *src, int choice);
char					*ft_strdup2(char const *s, int choice);
void					ft_strjoin2(char **line, const char *s1);
int						is_operator(char *c, int j);
void					line_positif(char *line);
/*****************************************************/

/******************** LST_UTILS ********************/
t_list_mini				*ft_lstlaste(t_list_mini *lst);
t_list_mini				*ft_lstnewe(void *content, t_type type);
void					ft_lstadde_back(t_list_mini **lst, t_list_mini *new);
void					ft_lstcleare(t_list_mini **lst, void (*del)(void *));
void					clear_lst(t_tab_struct *tab_struct, size_t size);
/*****************************************************/

/****************** FREE_FUNCTION ********************/
void					hd_free_inchild(t_global *glo);
void					free_splitted_line(t_split_line *del);
void					free_double_str(char **str);
void					free_inchild(t_global *glo);
char					**ft_free(char **str, int i);
/*****************************************************/

/*************** FREE_FUNCTION_SEQUEL ****************/
void					free_shell(t_global *global, char *input, int choice);
void					free_array(t_ptr_array pa);
void					free_path_malloc(t_global *global);
void					free_exec_malloc(t_global *global);
/*****************************************************/

/********************* PROMPT ************************/
int						get_git_branch(void);
char					*build_prompt(int opt);
/*****************************************************/

/****************** TMP_UTILS ************************/
void					display_split(t_tab_struct *tab_struct, t_global *info);
void					print_tab(char **str);
void					display(t_list_mini *head);
/*****************************************************/

#endif
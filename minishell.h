/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:48:24 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/26 21:42:45 by mparisse         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# define BB "\033[1;34m"
# define CB "\033[1;36m"
# define WB "\033[1;37m"
# define RB "\033[1;31m"
# define GB "\033[1;32m"
# define BRB "\033[1;33m"
# define EB "\033[0m"

typedef struct s_ptr_array
{
	size_t	size;
	size_t	capacity;
	void	**array;
	char	**path;
}	t_ptr_array;

typedef struct s_tab_struct
{
	long int		id;
	char	**commands;
	char	**env;
	char	**split_command;
}	t_tab_struct;

typedef struct s_global
{
	char			**basic_env;
	t_tab_struct	*struct_id;
	char			**env;
	char			**path;
	int				*forkstates;
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
	int		status;
	int		errnum;
}	t_command_status;

typedef void (*builtins)(t_global *, int);

t_ptr_array		pa_new(void);
void			pa_delete(t_ptr_array *pa);
void			pa_add(t_ptr_array *pa, void *ptr);
size_t			pa_size(t_ptr_array *pa);
void			*pa_get(t_ptr_array *pa, size_t index);
t_split_line	split_line(const char line[]);
int				ft_atoi(const char *nptr);
int				ft_isspace(char c);

/*********************** EXEC ***********************/
int				go_exec(t_global *global);
int				find_path_for_each_command(t_global *global);
int				forking(t_global *global, int i);
void			waiting(int *forkstates, int size_wait);
/***************************************************/

#endif
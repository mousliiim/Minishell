/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:48:24 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/24 05:45:44 by mmourdal         ###   ########.fr       */
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
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_ptr_array
{
	size_t	size;
	size_t	capacity;
	void	**array;
	char	**path;
}	t_ptr_array;

typedef struct s_split_line
{
	t_ptr_array	strings;
	const char	*error_message;
	size_t		error_position;
}	t_split_line;

typedef struct s_tab_struct
{
	int		id;
	char	*commands;
}	t_tab_struct;

typedef struct s_command_status
{
	bool	exit_shell;
	int		status;
	int		errnum;
}	t_command_status;

typedef struct s_global
{
	char			**basic_env;
	t_split_line	*split_line;
}	t_global;

t_ptr_array		pa_new(void);
void			pa_delete(t_ptr_array *pa);
void			pa_add(t_ptr_array *pa, void *ptr);
size_t			pa_size(t_ptr_array *pa);
void			*pa_get(t_ptr_array *pa, size_t index);
t_split_line	split_line(const char line[]);
int				ft_atoi(const char *nptr);
int				ft_isspace(char c);
int				parse(char *str);
#endif
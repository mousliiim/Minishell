/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_array.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:48:24 by mparisse          #+#    #+#             */
/*   Updated: 2023/02/24 01:41:53 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PTR_ARRAY_H
# define PTR_ARRAY_H

# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <ctype.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_ptr_array {
    size_t  size;
    size_t  capacity;
    void    **array;
    char    **path;
} t_ptr_array;

typedef struct s_split_line {
    t_ptr_array strings;
    const char  *error_message;
    size_t      error_position;
} t_split_line;

typedef struct s_command_status {
    bool exit_shell;
    int  status;
    int  errnum;
} t_command_status;

typedef struct s_global {
    char            **basic_env;   
    t_split_line    *split_line;
} t_global;

// void *pa_new(void);
// void pa_init(struct ptr_array *pa); 
t_ptr_array pa_new();

void pa_delete(t_ptr_array *pa);
void pa_add(t_ptr_array *pa, void *ptr);

size_t	pa_size(t_ptr_array *pa);
void * pa_get(t_ptr_array *pa, size_t index);
t_split_line split_line(const char line[], int stop);



#endif
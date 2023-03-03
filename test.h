/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 00:02:36 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/03 00:33:02 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_ptr_array
{
	size_t	size;
	size_t	capacity;
	void	**array;
}	t_ptr_array;

typedef struct s_tab_struct
{
	long int		id;
	char			**commands;
	char			**env;
	char			**split_command;
}	t_tab_struct;

typedef struct s_global
{
	char			**basic_env;
	t_tab_struct	*struct_id;
	t_ptr_array		personal_env;
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

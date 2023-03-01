/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:30:44 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/01 03:12:49 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(t_global *global, char *added)
{
	pa_add(&global->personal_env, ft_strdup(added));
}

int	export(t_global *global, int j)
{
	if (ft_isdigit(global->struct_id[j].split_command[1][0]) == 1
		&& global->struct_id[j].split_command[1][0] == '=')
	{
		ft_printf("bash: export : '%s': not a valid identfier\n",
					global->struct_id[j].split_command[1]);
		return (1);
	}
	pa_add(&global->personal_env,
			ft_strdup(global->struct_id[j].split_command[1]));
	return (0);
}

int	unset(t_global *glo, int i)
{
	(void) glo;
	(void) i;
	fprintf(stderr, "im unset");
	return (0);
}

int	cd(t_global *global, int i)
{
	int	status;
	int forkstatus;

	status = 0;
	if (status != 0)
		perror("Error changing directory");
    if (global->nb > 1)
	{
		forkstatus = fork();
		if (forkstatus == 0)
		{
			status = chdir(global->struct_id[i].split_command[1]);
			exit(0);
		}
		else
		{
			return (forkstatus);
		}
	}
	status = chdir(global->struct_id[i].split_command[1]);
	return (status);
}

builtins	find_ptr_builtin(char *ptr)
{
	static const builtins	func[3] = {&export, &unset, &cd};
	static const char		*str[3] = {"export", "unset", "cd"};
	int						i;

	i = 0;
	while (i < 3)
	{
		if (!ft_strcmp(str[i], ptr))
			return (func[i]);
		i++;
	}
	return (0);
}


int	go_exec(t_global *global)
{
	size_t		i;
	int			test;
	size_t		count_nb_bultin;
	builtins	ok;

	// tab[0] = &export;
	i = 0;
	count_nb_bultin = 0;
	find_path_for_each_command(global);
	global->forkstates = malloc(sizeof(int) * global->nb);
	// protege
	global->prev = -1;
	global->link[0] = -1;
	while (i < global->nb)
	{
		ok = find_ptr_builtin(global->struct_id[i].split_command[0]);
		if (ok)
		{
			test = ok(global, i);
			if (ok == &cd)
				global->forkstates[i] = test;
			else
				count_nb_bultin++;
		}
		else
		{
			pipe(global->link);
			forking(global, i);
		}
		i++;
	}
	waiting(global->forkstates, global->nb - count_nb_bultin);
	if (global->link[0] != -1)
		close(global->link[0]);
	free(global->forkstates);
	return (0);
}

int	find_path_for_each_command(t_global *global)
{
	int				i;
	int				j;
	t_tab_struct	*struc;
	char			*command_w_path;

	i = 0;
	struc = global->struct_id;
	if (!global->path)
		return (0);
	while (i < global->nb)
	{
		j = 0;
		while (global->path[j])
		{
			command_w_path = ft_sup_strjoin(global->path[j], '/',
					struc[i].split_command[0]);
			if (access(command_w_path, F_OK | X_OK) != -1)
			{
				free(struc[i].split_command[0]);
				struc[i].split_command[0] = command_w_path;
				break ;
			}
			free(command_w_path);
			j++;
		}
		i++;
	}
	return (0);
}

void	dupnclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

int	open_files(t_global *glo, int i)
{
	if (!ft_strcmp(glo->struct_id[i].split_command[1], ">"))
	{
		fprintf(stderr, "ok %s\n", glo->struct_id[i].split_command[1]);
	}
	return (0);
}

int	open_file(char *glo, int os)
{
	int	fd;
	
	fd = -1;
	if (os == 1)
	{
		fd = open(glo, O_TRUNC | O_CREAT | O_WRONLY, 0666);
		if (fd == -1)
			return (fd);
		dup2(fd, STDIN_FILENO);
	}
	return (fd);
}

int	open_states(t_global *glo, int j)
{
	int	i;
	int	fd;
	int	count;
	int	end;

	i = 0;
	count = 0;
	while (glo->struct_id[j].split_command[i])
	{
		if (!ft_strcmp(glo->struct_id[j].split_command[i], ">"))
		{
			if (count == 0)
				end = i;
			fprintf(stderr, "its good >> %s\n", glo->struct_id[j].split_command[i + 1]);
			fd = open_file((char *)glo->struct_id[j].split_command[i + 1], 1);
			dup2(fd, STDOUT_FILENO);
			count++;
		}
		i++;
	}
	glo->struct_id[j].split_command[end] = 0;
	return (fd);
}

int	forking(t_global *glo, int i)
{
	// int	os;

	glo->forkstates[i] = fork();
	if (glo->forkstates[i] == 0)
	{
		if (i != 0)
			dupnclose(glo->prev, STDIN_FILENO);
		if (i != (glo->nb - 1))
			dup2(glo->link[1], STDOUT_FILENO);
		// openfiles
		// open_files(glo, i);
		// open_states(glo, i);
		close(glo->link[0]);
		close(glo->link[1]);
		execve(glo->struct_id[i].split_command[0],
				glo->struct_id[i].split_command,
				(char **)glo->personal_env.array);
		exit(0);
	}
	else if (glo->forkstates[i] > 0)
	{
		close(glo->link[1]);
		if (glo->prev != -1)
			close(glo->prev);
		glo->prev = glo->link[0];
	}
	// ft_printf("-------------\n\n");
	return (0);
}


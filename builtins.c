/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 05:02:48 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/09 06:20:34 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	export(t_global *global, int j)
{
	int		stuff;
	int		idx_args;
	int		i;

	if (global->nb > 1)
		exit(0);
	idx_args = 1;
	while (global->struct_id[j].split_command[idx_args])
	{
		if (!global->struct_id[j].split_command[idx_args])
		{
			ft_printf("bash: export : '%s': not a valid identfier\n",
						global->struct_id[j].split_command[idx_args]);
			idx_args++;
			continue ;
		}
		if (ft_isdigit(global->struct_id[j].split_command[idx_args][0]) == 1
			|| global->struct_id[j].split_command[idx_args][0] == '=')
		{
			ft_printf("bash: export : '%s': not a valid identfier\n",
						global->struct_id[j].split_command[idx_args]);
			idx_args++;
			continue ;
		}
		stuff = ft_strchr(global->struct_id[j].split_command[idx_args], '=') - global->struct_id[j].split_command[idx_args];
		i = 0;
		if (stuff > 0)
		{
			while (global->personal_env.array[i])
			{
				if (!ft_strncmp(global->struct_id[j].split_command[idx_args], (char *)global->personal_env.array[i], stuff))
				{
					pa_pop(&global->personal_env, i);
					break ;
				}
				i++;
			}
			pa_add(&global->personal_env,
					ft_strdup(global->struct_id[j].split_command[idx_args]));
		}
		idx_args++;
	}
	return (0);
}

int	unset(t_global *glo, int j)
{
	int		i;
	int		idx_args;
	int		stuff;

	if (glo->nb > 1)
		exit(0);
	idx_args = 1;
	while (glo->struct_id[j].split_command[idx_args])
	{
		i = 0;
		while (glo->personal_env.array[i])
		{
			stuff = ft_strchr((char *)glo->personal_env.array[i], '=') - (char *)glo->personal_env.array[i];
			if (!ft_strncmp(glo->struct_id[j].split_command[idx_args], (char *)glo->personal_env.array[i],
					stuff))
			{
				pa_pop(&glo->personal_env, i);
				break ;
			}
			i++;
		}
		idx_args++;
	}
	return (0);
}

int	cd(t_global *global, int i)
{
	int	status;
	char *env;

	status = 0;
	if (!global->struct_id[i].split_command[1])
	{
		env = getenv("HOME");
		status = chdir(env);
		return (status);
	}
	status = chdir(global->struct_id[i].split_command[1]);
	if (status != 0)
	{
		ft_putstr_fd("miniboosted: cd : ", 2);
		ft_putstr_fd(global->struct_id[i].split_command[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (global->nb > 1)
		exit(0);
	return (status);
}

int	builtin_exit(t_global *global, int j)
{
	int	i;

	close(global->fd_solo_redirection);
	close(global->link[0]);
	if (global->nb > 1)
		exit(0);
	if (!global->struct_id[j].split_command[1])
		exit(0);
	i = 0;
	while (global->struct_id[j].split_command[1][i])
	{
		if (!ft_isdigit(global->struct_id[j].split_command[1][i]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(global->struct_id[j].split_command[1], 2);
			ft_putstr_fd(": numeric argument required", 2);

			exit(0);
		}
		i++;
	}
	exit ((unsigned char )ft_atoi(global->struct_id[j].split_command[1]));
}

int	print_env(t_global *glo, int j)
{
	int	i;

	(void) j;
	i = -1;
	while (glo->personal_env.array[++i])
		printf("%s\n", (char *)glo->personal_env.array[i]);
	if (glo->nb > 1)
		exit(0);
	return (0);
}

int	pwd(t_global *glo, int j)
{
	char	pwdd[PATH_MAX] = {0};

	if(!getcwd(pwdd, PATH_MAX))
		ft_printf("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	else
		printf("%s\n", pwdd);
	if (glo->nb > 1)
		exit(0);
	return (0);
}


int	echo(t_global *glo, int j)
{
	int	i;
	int	idx_args;
	int	option;
	size_t	len_expand;
	
	idx_args = 1;
	option = 0;
	while (glo->struct_id[j].split_command[idx_args] && !ft_strcmp(glo->struct_id[j].split_command[idx_args], "-n"))
	{
		idx_args++;
		option = 1;
	}
	while (glo->struct_id[j].split_command[idx_args])
	{
		if (glo->struct_id[j].split_command[idx_args][0] == '$')
		{
			if (!glo->struct_id[j].split_command[idx_args][1])
				printf("$");
			else
			{
				i = 0;
				len_expand = ft_strlen(&glo->struct_id[j].split_command[idx_args][1]);
				while (glo->personal_env.array[i])
				{
					if (!ft_strncmp(&glo->struct_id[j].split_command[idx_args][1], (char *)glo->personal_env.array[i], len_expand))
					{
						if (!(char *)&glo->personal_env.array[i][len_expand + 1])
							break ;
						printf("%s", (char *)&glo->personal_env.array[i][len_expand + 1]);
						break ;
					}
					i++;
				}
			}
		}
		else
		{
			if (glo->struct_id[j].split_command[idx_args])
			{
				printf("%s", glo->struct_id[j].split_command[idx_args]);
			}
		}
		if (option == 0)
			printf("\n");
		else
			printf(" ");
		idx_args++;
	}
	if (glo->nb > 1)
		exit(0);
	return (0);
}

char	**create_tab_color(char **cmd)
{
	int i;
	int size;
	int j;
	char **new;

	i = 0;
	while (cmd[i])
		i++;
	size = i + 2;
	new = malloc(sizeof(char *) * size);
	i = 1;
	j = 2;
	new[1] = ft_strdup("--color");
	new[0] = ft_strdup("/usr/bin/ls");
	while (cmd[i])
	{
		new[j] = ft_strdup(cmd[i]);
		j++;
		i++;
	}
	new[j] = 0;
	return (new);
}

int	ls_color(t_global *glo, int j)
{
	int	forks;
	int status = 0;
	
	glo->struct_id[j].split_command = create_tab_color(glo->struct_id[j].split_command);
	if (glo->nb == 1)
	{
		forks = fork();
		if (forks == 0)
		{
			execve(glo->struct_id[j].split_command[0], glo->struct_id[j].split_command, (char **)glo->personal_env.array);
		}
		waitpid(forks, &status, 0);
	}
	else
		execve(glo->struct_id[j].split_command[0], glo->struct_id[j].split_command, (char **)glo->personal_env.array);
	return (0);
}

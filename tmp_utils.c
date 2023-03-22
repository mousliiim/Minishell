/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 03:27:00 by mparisse          #+#    #+#             */
/*   Updated: 2023/03/22 02:17:51 by mmourdal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

extern int	g_status;

void	display_split(t_tab_struct *tab_struct, t_global *info)
{
	size_t	i;
	size_t	j;

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
		write(2, "\n", 1);
		i++;
	}
}

void	print_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_printf("%s\n", str[i++]);
}

void	display(t_list_mini *head)
{
	char		*display;
	t_list_mini	*temp;

	temp = head;
	ft_printf("\n*******************\nDISPLAY LINKED LIST : \n");
	while (temp != NULL)
	{
		if (temp->redirect == OUT)
			display = ">";
		else if (temp->redirect == IN)
			display = "<";
		else if (temp->redirect == HERE_DOC)
			display = "<<";
		else if (temp->redirect == APPEND)
			display = ">>";
		ft_printf("*******************\n");
		ft_printf("File_name : '%s'\n", temp->file_name);
		ft_printf("Type enum : %d\n", temp->redirect);
		ft_printf("View enum : %s\n", display);
		ft_printf("*******************\n");
		temp = temp->next;
	}
}

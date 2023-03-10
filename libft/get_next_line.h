/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:44:06 by mmourdal          #+#    #+#             */
/*   Updated: 2023/03/06 20:53:32 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_get_line(char *buffer);
char	*ft_strjoin3(char *buffer, char *str);
char	*ft_read_next_buffer(char *buffer);
size_t	ft_strlen2(char *str);
char	*ft_read_buffer(int fd, char *buffer);
char	*ft_strchr3(char *s, int c);

#endif
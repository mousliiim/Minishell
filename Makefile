# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 22:36:18 by mparisse          #+#    #+#              #
#    Updated: 2023/03/09 04:04:42 by mparisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c pa_utils.c utils.c exec.c parsing.c builtins.c rafter.c \
		path_utils.c here_docs.c prompt.c

OBJS = ${SRCS:.c=.o}

NAME = minishell

LIBS = libft.a -lreadline

CFLAGS = -Wall -Werror -Wextra -lreadline

CC = cc -g

all : ${NAME}

${NAME} : ${OBJS}
	@make --no-print-directory -C libft/
	@cp libft/libft.a .
	@echo -n "Compiling libft..." 
	${CC} ${CFLAGS} ${OBJS} ${LIBS}   -o ${NAME}

clean : 
	rm -rf ${OBJS}
	make -C libft/ clean

fclean : clean
	rm -rf ${NAME}
	rm -rf libft.a
	make -C libft/ fclean

re : fclean all

.c.o :
	${CC} -Wall -Werror -Wall -c $< -o ${<:.c=.o}

.PHONY : libft clean fclean re
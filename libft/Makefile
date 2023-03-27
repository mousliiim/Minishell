# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 17:21:41 by mparisse          #+#    #+#              #
#    Updated: 2023/03/27 03:23:37 by mparisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c \
ft_strlen.c ft_tolower.c ft_toupper.c ft_memset.c ft_bzero.c \
ft_strdup.c ft_memcpy.c ft_substr.c ft_strchr.c \
ft_strrchr.c ft_strncmp.c ft_strcmp.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_strlcat.c ft_strnstr.c ft_strjoin.c ft_memchr.c ft_memcmp.c \
ft_memmove.c ft_strtrim.c  ft_abs.c\
ft_striteri.c ft_strmapi.c ft_calloc.c \
ft_strlcpy.c ft_split.c ft_itoa.c ft_utils.c ft_printf.c ft_swap.c \
ft_strndup.c ft_sup_strjoin.c ft_isspace.c ft_strcat.c ft_strcpy.c \

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${BONUS:.c=.o}

NAME = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra 

all:	${NAME}

.c.o :
	@cc -Wall -Werror -Wextra -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		@ar rcs libft.a ${OBJS}

bonus:	${OBJS} ${OBJS_BONUS}
	ar rcs ${NAME} ${OBJS} ${OBJS_BONUS}

norme:
	norminette ${SRCS} ${BONUS} libft.h

clean:
	@rm -rf ${OBJS}
	@rm -rf ${OBJS_BONUS}

fclean:	clean
	@rm -rf ${NAME}

re:	fclean ${NAME}

.PHONY : all bonus norme clean fclean re
.SILENT:

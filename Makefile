# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmourdal <mmourdal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 03:16:15 by mmourdal          #+#    #+#              #
#    Updated: 2023/03/12 05:18:13 by mmourdal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  ASCII ART                                   #
################################################################################

BLUE	= \033[1;36m
RED		= \033[1;31m
WHITE	= \033[1;37m
BLINK	= \033[5m
END		= \033[0m

ART_NAME_1 =             ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█               \n
ART_NAME_2 =           ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███               \n
ART_NAME_3 =           ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███               \n
ART_NAME_4 =           ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███               \n
ART_NAME_5 =           ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███               \n
ART_NAME_6 =           ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███               \n
ART_NAME_7 =		   ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄         \n
ART_NAME_8 =            ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██         \n

PRINT_NAME = printf "\n $(BLUE) %0s $(ART_NAME_1) $(ART_NAME_2) $(ART_NAME_3) $(ART_NAME_4) $(ART_NAME_5) $(ART_NAME_6) $(ART_NAME_7) %0s $(ART_NAME_8) $(END)\n"

################################################################################
#                                  SOURCES                                     #
################################################################################

PARSE_DIR	= parse
EXEC_DIR	= exec
BUILT_DIR	= builtins
UTILS_DIR	= utils
SIGNAL_DIR	= signal
ENV_DIR		= env
FREE_DIR	= free

SRC_FILES	=	$(addprefix parse/, \
				parsing.c		ptr_a_utils.c		ptr_a_utils_second.c		rafter.c		split_parsing.c \
				expand.c) \
				\
				$(addprefix exec/, \
				exec.c		here_docs.c) \
				\
				$(addprefix builtins/, \
				cd.c		echo.c		exit.c		export.c		ls_color.c		pwd.c		unset.c) \
				\
				$(addprefix utils/, \
				lst_utils.c	prompt.c		utils.c) \
				\
				$(addprefix signal/, \
				signal.c) \
				\
				$(addprefix env/, \
				env.c		path_utils.c) \
				\
				$(addprefix free/, \
				free_function.c) \
				\
				main.c tmp_utils.c

################################################################################
#                                  OBJETS                                      #
################################################################################

OBJS_DIR	= objets
OBJS		= $(SRC_FILES:%.c=$(OBJS_DIR)/%.o)

################################################################################
#                               OTHER LIBRARY                                  #
################################################################################

LIB_DIR = libft

################################################################################
#                                COMPILATION                                   #
################################################################################

CC		= @cc
CFLAGS	= -g3 -Wall -Wextra -Werror
CIFLAGS	= -Iincludes -I$(LIB_DIR)/includes
CCLIED	= -L$(LIB_DIR) -lft -lreadline
MAKE	= @make --no-print-directory

################################################################################
#                                  MAKEFILE                                    #
################################################################################

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(CIFLAGS) $(OBJS) $(CCLIED) -o $(NAME)

$(OBJS_DIR) :
	@$(PRINT_NAME)
	@printf "$(BLUE)%20s Compilation de la librairie $(END)$(WHITE)$(LIB_DIR)...\n"
	$(MAKE) -C $(LIB_DIR)
	@printf "$(BLUE)%18s Compilation de la librairie $(END)$(BLINK)$(WHITE)$(LIB_DIR) terminée$(END)\n\n"
	@sleep 0.7
	@printf "$(BLUE)%20s Création des dossiers content les $(END)$(WHITE).o : \n"
	@sleep 0.2
	@printf "$(BLUE)%24s Création du dossier $(END)$(WHITE)$(OBJS_DIR)...\n"
	@mkdir $(OBJS_DIR)
	@sleep 0.2
	@printf "$(BLUE)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(PARSE_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(PARSE_DIR)
	@sleep 0.2
	@printf "$(BLUE)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(EXEC_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(EXEC_DIR)
	@sleep 0.2
	@printf "$(BLUE)%20s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(BUILT_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(BUILT_DIR)
	@sleep 0.2
	@printf "$(BLUE)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(UTILS_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(UTILS_DIR)
	@sleep 0.2
	@printf "$(BLUE)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(SIGNAL_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(SIGNAL_DIR)
	@sleep 0.2
	@printf "$(BLUE)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(ENV_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(ENV_DIR)
	@sleep 0.2
	@printf "$(BLUE)%21s Création du dossier $(END)$(WHITE)$(OBJS_DIR)/$(FREE_DIR)...\n"
	@mkdir $(OBJS_DIR)/$(FREE_DIR)
	@sleep 0.2
	@printf "$(BLUE)%20s Création des dossiers $(END)$(BLINK)$(WHITE)objets terminée$(END)\n\n"
	@sleep 0.9
	@printf "$(BLUE)%24s Compilation de $(END)$(WHITE)$(NAME)...\n"
	@sleep 0.2
	@printf "$(BLUE)%21s Compilation de $(END)$(BLINK)$(WHITE)$(NAME) terminée$(END)\n\n"

$(OBJS) : $(OBJS_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(CIFLAGS) -c $< -o $@

clean :
	$(MAKE) clean -C $(LIB_DIR)
	@rm -rf $(OBJS_DIR)
	@printf "\n$(BLUE)Suppression des objets de la librairie : $(END)$(WHITE)$(LIB_DIR) [✅]$(END)\n"
	@printf "$(BLUE)%6s Suppression du dossier : $(END)$(WHITE)$(OBJS_DIR) [✅]$(END)\n\n"
	
fclean: clean
	$(MAKE) fclean -C $(LIB_DIR)
	@rm -rf $(NAME)
	@printf "$(BLUE)%2s Suppression de l'exécutable : $(END)$(WHITE)$(NAME) [✅]$(END)\n\n"
	
re : fclean all

.PHONY: all clean fclean re

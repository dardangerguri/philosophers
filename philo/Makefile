# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dardangerguri <dardangerguri@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 16:24:12 by dgerguri          #+#    #+#              #
#    Updated: 2023/07/14 19:07:52 by dardangergu      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
FLAGS = -Wall -Wextra -Werror -pthread -fsanitize=address

INCLUDE = -I ./includes/

SRC_DIR = ./srcs/

SRC =	main.c \
		utils.c \
		validate.c \
		error.c \
		init.c



OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(BLUE)Compiling $(NAME) project! $(RESET)"
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Compiled $(NAME) project! $(RESET)"

clean:

	@$(RM) -rf $(OBJ_DIR)
	@echo "$(RED)Removed object files!$(RESET)"

fclean: clean
	@$(RM) -rf $(NAME)
	@echo "$(RED)Removed $(NAME)!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
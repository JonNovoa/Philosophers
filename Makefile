# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnovoa-a <jnovoa-a@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/29 17:25:23 by jnovoa-a          #+#    #+#              #
#    Updated: 2025/12/29 17:25:38 by jnovoa-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
RM = rm -f

SRC_DIR = src
INC_DIR = includes
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parsing.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/routine.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/monitor.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I$(INC_DIR)

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully! $(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled:  $<$(RESET)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)🗑️  Object files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)🗑️  $(NAME) removed$(RESET)"

re: fclean all

. PHONY: all clean fclean re
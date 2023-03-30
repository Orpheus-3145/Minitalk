# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fra <fra@student.42.fr>                      +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/14 18:27:31 by anonymous     #+#    #+#                  #
#    Updated: 2023/03/30 02:14:35 by fra           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

NAME := libft.a
MAIN := main
SRC_DIR := sources
OBJ_DIR := objects
INCLUDE  := include

SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS := $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))
HEADERS :=$(wildcard $(INCLUDE)/*.h)

CC  := gcc
IFLAGS := -I $(INCLUDE)
CFLAGS  := -Wall -Wextra -Werror
LFLAGS  := -rcs

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \x1b[34;01m
RESET = \x1b[0m
YELLOW = \x1b[33;01m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(HEADERS)
	@ar $(LFLAGS) $(NAME) $(OBJS)
	@printf "(libft) $(YELLOW)Created archive $(NAME)$(RESET)\n"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@
	@printf "(libft) $(BLUE)Created object $$(basename $@)$(RESET)\n"

clean:
	@for file in $(shell find $(OBJ_DIR) -type f -name '*.o'); do \
		rm -f $$file;	\
		printf "(libft) $(RED)Removed object $$(basename $$file)$(RESET)\n"; \
	done

fclean:
	@-rm -f $(NAME)
	@printf "(libft) $(RED)Removed $(NAME)$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
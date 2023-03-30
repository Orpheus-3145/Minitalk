# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fra <fra@student.42.fr>                      +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/30 15:27:27 by faru          #+#    #+#                  #
#    Updated: 2023/03/30 02:18:54 by fra           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

SRC_DIR := sources
OBJ_DIR := objects
LIBFT_DIR := libft
SERVER := server
CLIENT := client
SRV_SRC := $(SRC_DIR)/$(SERVER).c
SRV_OBJ := $(OBJ_DIR)/$(SERVER).o
CNT_SRC := $(SRC_DIR)/$(CLIENT).c
CNT_OBJ := $(OBJ_DIR)/$(CLIENT).o
HEADER := minitalk.h
LIBFT := $(LIBFT_DIR)/libft.a

CC  := gcc
WFLAGS  := -Wall -Wextra -Werror
LFLAGS  := $(LIBFT)
IFLAGS := -Iinclude -I$(LIBFT_DIR)/include

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \x1b[34;01m
RESET = \x1b[0m
YELLOW = \x1b[33;01m

all: $(LIBFT) $(OBJ_DIR) $(SERVER) $(CLIENT)
	
$(SERVER): $(SRV_SRC)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $(SRV_SRC) -o $(SRV_OBJ)
	@printf "(minitalk) $(BLUE)Created object $$(basename $(SRV_OBJ))$(RESET)\n"
	@$(CC) $(WFLAGS) $(IFLAGS) $(SRV_OBJ) $(LFLAGS) -o $(SERVER)
	@printf "(minitalk) $(GREEN)Created executable $(SERVER)$(RESET)\n"

$(CLIENT): $(CNT_SRC)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $(CNT_SRC) -o $(CNT_OBJ)
	@printf "(minitalk) $(BLUE)Created object $$(basename $(CNT_OBJ))$(RESET)\n"
	@$(CC) $(WFLAGS) $(IFLAGS) $(CNT_OBJ) $(LFLAGS) -o $(CLIENT)
	@printf "(minitalk) $(GREEN)Created executable $(CLIENT)$(RESET)\n"

$(LIBFT):
	@cd libft && $(MAKE) --no-print-directory

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR) --quiet
	@-rm -rf $(OBJ_DIR)
	@printf "(minitalk) $(RED)Removed direcory objects/$(RESET)\n"

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --quiet
	@-rm -f $(SERVER) $(CLIENT)
	@printf "(minitalk) $(RED)Removed $(SERVER)$(RESET)\n"
	@printf "(minitalk) $(RED)Removed $(CLIENT)$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus

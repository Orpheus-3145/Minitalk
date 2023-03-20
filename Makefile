# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fra <fra@student.42.fr>                      +#+                      #
#                                                    +#+                       #
#    Created: 2022/11/30 15:27:27 by faru          #+#    #+#                  #
#    Updated: 2023/02/22 21:01:31 by faru          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

SRC_DIR := sources
OBJ_DIR := objects
TOOLS_DIR := tools
SERVER := server
CLIENT := client
SRV_SRC = $(SRC_DIR)/$(SERVER).c
CNT_SRC = $(SRC_DIR)/$(CLIENT).c
CNT_SRC_BNS = $(SRC_DIR)/$(CLIENT)_bonus.c
SRV_OBJ := $(OBJ_DIR)/$(SERVER).o
CNT_OBJ := $(OBJ_DIR)/$(CLIENT).o
CNT_OBJ_BNS := $(OBJ_DIR)/$(CLIENT)_bonus.o
TOOLS := $(wildcard $(TOOLS_DIR)/*.c)
OBJS := $(subst $(TOOLS_DIR), $(OBJ_DIR), $(TOOLS:.c=.o))
HEADER :=$(wildcard $(INCLUDE)/*.h)

LIB_LIBFT := libft.a
LIB_MT := libmt.a

CC  := gcc
WFLAGS  := -Wall -Wextra -Werror
LFLAGS  := $(LIB_MT) libft/$(LIB_LIBFT)
IFLAGS := -Iinclude -Ilibft/include

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \x1b[34;01m
RESET = \x1b[0m
YELLOW = \x1b[33;01m

all: $(LIB_MT) $(LIB_LIBFT) $(SERVER) $(CLIENT)
	
$(SERVER): $(SRV_SRC)
	@$(CC) $(WFLAGS) $(IFLAGS) -c $(SRV_SRC) -o $(SRV_OBJ)
	@printf "$(BLUE)Created object $(subst $(OBJ_DIR),,$(SRV_OBJ))$(RESET)\n"
	@$(CC) $(WFLAGS) $(IFLAGS) $(SRV_OBJ) $(LFLAGS) -o $(SERVER)
	@printf "$(GREEN)Created executable $(SERVER)$(RESET)\n"

$(CLIENT): $(CNT_SRC)
	@$(CC) $(WFLAGS) $(IFLAGS) -c $(CNT_SRC) -o $(CNT_OBJ)
	@printf "$(BLUE)Created object $(subst $(OBJ_DIR),,$(CNT_OBJ))$(RESET)\n"
	@$(CC) $(WFLAGS) $(IFLAGS) $(CNT_OBJ) $(LFLAGS) -o $(CLIENT)
	@printf "$(GREEN)Created executable $(CLIENT)$(RESET)\n"

$(LIB_MT): $(OBJ_DIR) $(OBJS) $(HEADER)
	@ar -rcs $(LIB_MT) $(OBJS)
	@printf "$(YELLOW)Created archive $(LIB_MT)$(RESET)\n"

$(LIB_LIBFT):
	@cd libft && $(MAKE) --no-print-directory

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(TOOLS_DIR)/%.c
	@$(CC) $(WFLAGS) $(IFLAGS) -c $^ -o $@
	@printf "$(BLUE)Created object $(subst $(OBJ_DIR),,$@)$(RESET)\n"

bonus: $(SERVER) $(CNT_SRC_BNS)
	@$(CC) $(WFLAGS) $(IFLAGS) -c $(CNT_SRC_BNS) -o $(CNT_OBJ_BNS)
	@printf "$(BLUE)Created object $(subst $(OBJ_DIR),,$(CNT_OBJ_BNS))$(RESET)\n"
	@$(CC) $(WFLAGS) $(IFLAGS) $(CNT_OBJ_BNS) $(LFLAGS) -o $(CLIENT)
	@printf "$(GREEN)Created executable $(CLIENT)$(RESET)\n"

clean:
	@rm -f $(OBJS) $(SRV_OBJ) $(CNT_OBJ) $(CNT_OBJ_BNS) $(SRV_OBJ_BNS)
	@printf "$(RED)Removing files $(OBJS) $(SRV_OBJ) $(CNT_OBJ)$(RESET)\n"
	@cd libft && $(MAKE) clean --no-print-directory

fclean: clean
	@-rm -f $(SERVER) $(CLIENT) $(LIB_MT) $(SERVER)_bonus $(CLIENT)_bonus
	@printf "$(RED)Removing $(CLIENT), $(SERVER) and $(LIB_MT)$(RESET)\n"
	@cd libft && $(MAKE) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re bonus

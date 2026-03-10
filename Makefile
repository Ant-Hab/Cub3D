# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/29 17:14:37 by achowdhu          #+#    #+#              #
#    Updated: 2026/03/10 17:01:21 by achowdhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================================
#           Project Information
# ========================================

NAME        := cub3d

# Compiler and Flags
CC          := cc
CFLAGS		:= -Wall -Wextra -Werror -g

# Directories
SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := include
LIBFT_DIR   := libft
MLX_DIR     := MLX42

# Source and Object Files
SRCS        := main.c \
               src/parsing/parse.c \
               src/parsing/parse_identifiers.c \
               src/parsing/parse_map.c \
               src/parsing/parse_utils.c \
               src/utils/utils.c \
               src/utils/debug.c \
               src/execution/game.c \
			   src/execution/init_game.c \
               src/execution/raycast.c \
               src/execution/drawing.c \
			   src/execution/movement.c \
			   src/execution/utilities.c \
               src/execution/textures.c

OBJS        := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT       := $(LIBFT_DIR)/libft.a
MLX_LIB     := $(MLX_DIR)/libmlx42.a -lglfw -ldl -lm
INC         := -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR)/include

# ========================================
#               Colors
# ========================================

GREEN       := \033[0;32m
YELLOW      := \033[0;33m
RESET       := \033[0m

# ========================================
#               Rules
# ========================================

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_DIR)/libmlx42.a
	@echo "$(GREEN)[Linking]$(RESET) $(NAME)"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(MLX_DIR)/libmlx42.a -lglfw -ldl -lm -o $(NAME)
	@echo "$(GREEN)✔ $(NAME) built successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@echo "$(GREEN)[Compiling]$(RESET) $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(YELLOW)[Building]$(RESET) libft"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@echo "$(YELLOW)[Building]$(RESET) MLX42"
	@cd $(MLX_DIR) && cmake . && make

clean:
	@echo "$(YELLOW)[Cleaning]$(RESET) object files"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "$(YELLOW)[Removing]$(RESET) $(NAME) and $(NAME).exe"
	@rm -f $(NAME) $(NAME).exe
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ========================================
#              Special Rules
# ========================================

.PHONY: all clean fclean re

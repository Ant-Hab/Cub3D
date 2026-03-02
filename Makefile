# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/29 17:14:37 by achowdhu          #+#    #+#              #
#    Updated: 2026/03/02 15:53:04 by jaeklee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================================
#           Project Information
# ========================================

# NAME        := cub3d

# # Compiler and Flags
# CC          := cc
# CFLAGS		:= -Wall -Wextra -Werror -g

# # Directories
# SRC_DIR     := src
# OBJ_DIR     := obj
# INC_DIR     := include
# LIBFT_DIR   := libft

# # Source and Object Files
# SRCS        := $(shell find $(SRC_DIR) -name "*.c")
# OBJS        := $(addprefix $(OBJ_DIR)/,$(SRCS:$(SRC_DIR)/%.c=%.o))

# # Library
# LIBFT       := $(LIBFT_DIR)/libft.a
# MLX_DIR := mlx42
# MLX_LIB := -L$(MLX_DIR) -lmlx42 -lglfw -ldl -lm


# INC := -I$(INC_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR)/include

# # ========================================
# #               Colors
# # ========================================

# GREEN       := \033[0;32m
# YELLOW      := \033[0;33m
# RESET       := \033[0m

# # ========================================
# #               Rules
# # ========================================

# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 	@echo "$(GREEN)[Linking]$(RESET) $(NAME)"
# 	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)
# 	@echo "$(GREEN)✔ $(NAME) built successfully!$(RESET)"

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
# 	@echo "$(GREEN)[Compiling]$(RESET) $<"
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# $(LIBFT):
# 	@echo "$(YELLOW)[Building]$(RESET) libft"
# 	@$(MAKE) -C $(LIBFT_DIR)

# clean:
# 	@echo "$(YELLOW)[Cleaning]$(RESET) object files"
# 	@rm -rf $(OBJ_DIR)
# 	@$(MAKE) -C $(LIBFT_DIR) clean

# fclean: clean
# 	@echo "$(YELLOW)[Removing]$(RESET) $(NAME)"
# 	@rm -f $(NAME)
# 	@$(MAKE) -C $(LIBFT_DIR) fclean

# re: fclean all

# # ========================================
# #              Special Rules
# # ========================================

# .PHONY: all clean fclean re
# .SECONDARY:
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
# Source and Object Files
SRCS        := $(shell find $(SRC_DIR) -name "*.c")
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(GREEN)[Compiling]$(RESET) $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(YELLOW)[Building]$(RESET) libft"
	@$(MAKE) -C $(LIBFT_DIR)

# Build MLX42 if not exists
$(MLX_LIB):
	@echo "$(YELLOW)[Building]$(RESET) MLX42"
	@cd $(MLX_DIR) && cmake . && make

clean:
	@echo "$(YELLOW)[Cleaning]$(RESET) object files"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "$(YELLOW)[Removing]$(RESET) $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ========================================
#              Special Rules
# ========================================

.PHONY: all clean fclean re

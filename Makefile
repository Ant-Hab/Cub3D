# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achowdhu <achowdhu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 14:25:57 by achowdhu          #+#    #+#              #
#    Updated: 2026/02/17 13:33:10 by achowdhu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========================================
#           Project Information
# ========================================

NAME        := cub3d

# Compiler and Flags
CC          := cc
CFLAGS      := -Wall -Wextra -Werror

# Directories
SRC_DIR     := src
OBJ_DIR     := obj
LIBFT_DIR   := libft
MLX_DIR     := minilibx

# Source and Object Files
SRCS        := parse_files.c
OBJS        := $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

# Library
LIBFT       := $(LIBFT_DIR)/libft.a
MLX_LIB     := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

# Includes
INC         := -Iinclude -I$(LIBFT_DIR)/include -I$(MLX_DIR)

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

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)[Linking]$(RESET) $(NAME)"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)
	@echo "$(GREEN)✔ $(NAME) built successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(GREEN)[Compiling]$(RESET) $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(YELLOW)[Building]$(RESET) libft"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "$(YELLOW)[Cleaning]$(RESET) object files"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)[Removing]$(RESET) $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)✔ All files removed successfully!$(RESET)"

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re

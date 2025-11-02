# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 11:19:05 by sjuan-ma          #+#    #+#              #
#    Updated: 2025/11/02 18:41:27 by sjuan-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = so_long
CC      = cc
CFLAGS  = -Wall -Wextra -Werror #-fsanitize=address -g3

MLX42   = MLX42/build/libmlx42.a
LIBFT_DIR = libft
LIBFT   = $(LIBFT_DIR)/libft.a
LIBS    = -ldl -lglfw -pthread -lm

INCLUDES = -Iinclude -Iget_next_line -Ilibft -IMLX42/include

SRC_DIR = src
GNL_DIR = get_next_line
OBJ_DIR = obj

SRC = $(SRC_DIR)/so_long.c \
	  $(SRC_DIR)/init_img.c \
      $(SRC_DIR)/map.c \
      $(SRC_DIR)/hook.c \
      $(SRC_DIR)/utils.c \
      $(SRC_DIR)/moves.c \
      $(SRC_DIR)/render.c \
      $(SRC_DIR)/validate_map.c \
      $(SRC_DIR)/validate_path.c \
      $(GNL_DIR)/get_next_line.c \
      $(GNL_DIR)/get_next_line_utils.c

OBJ = $(OBJ_DIR)/so_long.o \
      $(OBJ_DIR)/init_img.o \
      $(OBJ_DIR)/map.o \
      $(OBJ_DIR)/hook.o \
      $(OBJ_DIR)/utils.o \
      $(OBJ_DIR)/moves.o \
      $(OBJ_DIR)/render.o \
      $(OBJ_DIR)/validate_map.o \
      $(OBJ_DIR)/validate_path.o \
      $(OBJ_DIR)/get_next_line.o \
      $(OBJ_DIR)/get_next_line_utils.o

all: $(NAME)

$(NAME): $(OBJ) $(MLX42) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX42) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "proyecto compilado correctamente."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@echo "libft compilada."

$(MLX42):
	@cmake -B MLX42/build MLX42 > /dev/null 2>&1
	@make -C MLX42/build > /dev/null 2>&1
	@echo "MLX compilada."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null
	@echo " Compilado : $<"

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ > /dev/null

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	-@$(MAKE) -C MLX42/build clean > /dev/null 2>&1 || true
	@echo "archivos objeto y temporales eliminados."

fclean: clean
	@rm -f $(NAME)
	@rm -f MLX42/build/libmlx42.a
	@rm -rf MLX42/build
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@echo "todo limpio: binarios, libft, gnl, y MLX42."

re: fclean all

.PHONY: all clean fclean re libmlx lbft get_next_line

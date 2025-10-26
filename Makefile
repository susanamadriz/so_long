# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 11:19:05 by sjuan-ma          #+#    #+#              #
#    Updated: 2025/10/26 18:30:14 by sjuan-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#  gcc:
# 	gcc src/*.c get_next_line/*.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o so_long 

NAME    = so_long
CC      = cc
CFLAGS  = -Wall -Wextra -Werror # -fsanitize=address -g3

MLX42   = MLX42/build/libmlx42.a
LIBFT_DIR = libft
LIBFT   = $(LIBFT_DIR)/libft.a
LIBS    = -ldl -lglfw -pthread -lm

INCLUDES = -Iinclude -Iget_next_line -Ilibft -IMLX42/include

SRC_DIR = src
GNL_DIR = get_next_line
OBJ_DIR = obj

# Fuentes
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

# Objetos en obj/
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# ------------------------------
# REGLAS
# ------------------------------
all: $(NAME)

# Ejecutable
$(NAME): $(OBJ) $(MLX42) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX42) $(LIBFT) $(LIBS) -o $(NAME)

# Compilar libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compilar todos los .c a obj/*.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpiar objetos
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Limpiar objetos y binario
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 11:19:05 by sjuan-ma          #+#    #+#              #
#    Updated: 2025/10/18 18:34:56 by susanamadri      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#  gcc:
# 	gcc src/*.c get_next_line/*.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o so_long 

# ------------------------------
# VARIABLES
# ------------------------------
NAME    = so_long
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

MLX42   = MLX42/build/libmlx42.a
LIBFT   = libft/libft.a
LIBS    = -ldl -lglfw -pthread -lm

INCLUDES = -Iinclude -Iget_next_line -IMLX42/include

# ------------------------------
# FUENTES
# ------------------------------
SRC_DIR = src
GNL_DIR = get_next_line
LIBFT_DIR = libft

SRC = $(SRC_DIR)/so_long.c \
      $(SRC_DIR)/map.c \
      $(SRC_DIR)/hook.c \
      $(SRC_DIR)/utils.c \
      $(SRC_DIR)/moves.c \
      $(GNL_DIR)/get_next_line.c \
      $(GNL_DIR)/get_next_line_utils.c \
	  $(SRC_DIR)/render.c \
 	  $(SRC_DIR)/validate_map.c \
      $(SRC_DIR)/validate_path.c
# ------------------------------

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

# ------------------------------
# REGLAS
# ------------------------------
all: $(NAME)

# Compilar el ejecutable
$(NAME): $(OBJ) $(MLX42) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX42) $(LIBFT) $(LIBS) -o $(NAME)

# Build libft static library
$(LIBFT):
	$(MAKE) -C libft

# Compilar los .c a .o dentro de obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpiar objetos
clean:
	rm -rf $(OBJ_DIR)

# Limpiar objetos y binario
fclean: clean
	rm -f $(NAME)

# Recompilar todo
re: fclean all

.PHONY: all clean fclean re


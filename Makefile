# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/05 11:19:05 by sjuan-ma          #+#    #+#              #
#    Updated: 2025/02/08 19:22:45 by sjuan-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

 gcc:
	gcc *.c get_next_line/*.c MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm 
# -g3 -fsanitize=address
	
# MAKEFLAGS	= --no-print-directory --silent

# NAME	 = so_long

# CC = cc

# CFLAGS	 =	-Wextra -Wall -Werror -Wunreachable-code
# CFLAGS	 += -I includes
# CFLAGS	 += -I libft
# CFLAGS	 += -I GNL
# CFLAGS	 += -O3

# DEBUG	 =	-g3 -fsanitize=address

# CPPFLAGS =	-MMD

# LIBMLX	= ./libs/MLX42
# LIBFT	= ./libs/libft

# HEADERS = -I ./includes -I $(LIBMLX)/include -I $(LIBFT)

# LIBS	=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
# LIBS	+=	$(LIBFT)/libft.a

# SRC = main.c so_long.c graphics.c map.c player.c

# OBJS = $(patsubst %.c, objs/%.o, $(SRC))
# DEPS = $(OBJS:.o=.d)

# all: $(NAME)

# libmlx:
# 	@cmake -DDEBUG=0 $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# libft:
# 	@make -C $(LIBFT)

# $(NAME): $(OBJS) libmlx libft
# 	$(CC) $(DEBUG) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && printf "Linking: $(NAME)\n"

# objs/%.o: %.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

# clean:
# 	@rm -rf objs
# 	@rm -rf $(LIBMLX)/build
# 	@make fclean -C $(LIBFT)

# fclean: clean
# 	@rm -rf $(NAME)

# re: fclean all

# -include $(DEPS)

# .PHONY: all clean fclean re libmlx libft

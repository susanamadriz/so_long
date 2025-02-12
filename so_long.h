/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:39:56 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/02/08 20:16:32 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"

typedef struct s_map {
    char **grid;
    int width;
    int height;
} t_map;

// Declara las funciones en este archivo

size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int char_check(char **map);

t_map *load_map(const char *filename);
int validate_map(t_map *map);
char ** read_map(char *archivo);
int count_map(char *archivo);

#endif

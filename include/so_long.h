/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:39:56 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/16 18:48:42 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "get_next_line.h"

# define TILE 64

typedef struct s_map {
    char    **grid;
    int     width;
    int     height;
}   t_map;

typedef struct s_game {
    mlx_t       *mlx;
    mlx_image_t *img_player;
    mlx_image_t *img_wall;
    mlx_image_t *img_floor;
    mlx_image_t *img_exit;
    mlx_image_t *img_collect;
    t_map       *map;
    int         player_x;
    int         player_y;
    int         moves;
    int         collectibles; // 👈 cantidad de collectibles restantes
}   t_game;

// hook.c
void my_keyhook(mlx_key_data_t keydata, void *param);

// utils.c
int     ft_arrlen(char **arr);

// map.c
char    **read_map(char *file);
int     count_map(char *file);

// so_long.c
void    draw_map(t_game *game);
void    hook(void *param);

// moves.c
void    move_player(t_game *game, int dx, int dy);

// render.c
void    draw_map_render(t_game *game);

#endif

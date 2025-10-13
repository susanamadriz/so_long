/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:39:56 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/14 00:01:02 by susanamadri      ###   ########.fr       */
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

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img_player;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_floor;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_collect;
	t_map		*map;
	int			player_x;
	int			player_y;
	int			moves;
	int			collectibles; // 👈 cantidad de collectibles restantes
}	t_game;

// hook.c
void	my_keyhook(mlx_key_data_t keydata, void *param);

// utils.c
int		ft_arrlen(char **arr);
int		check_ber(const char *filename);
void	free_map(char **map);
char	**copy_map(t_map *map);
static int	print_error(const char *msg);

// map.c
char	**read_map(char *file);
int		count_map(char *file);

// so_long.c
void	draw_map(t_game *game);

// moves.c
void	move_player(t_game *game, int dx, int dy);

// render.c
void	draw_map_render(t_game *game);

/* validate_map.c */
int		char_check(char **map);
int		validate_map_full(t_map *map, int *start_x, int *start_y);
void	free_map(char **map);

void	draw_map(t_game *game);

#endif

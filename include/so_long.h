/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:39:56 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/26 18:19:29 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "get_next_line.h"

# define TILE 64

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		p;
	int		e;
	int		c;
	int		sx;
	int		sy;
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
// void	free_map(char **map);
char	**copy_map(t_map *map);
int		print_error(const char *msg);

// map.c
char	**read_map(char *file);
int		count_map(char *file);

// so_long.c
void	draw_map(t_game *game);

// moves.c
void	move_player(t_game *game, int dx, int dy);

// render.c
void	draw_map_render(t_game *game);
void	free_game2(t_game *game);

/* validate_map.c */
int		char_check(char **map);
int		validate_map_full(t_map *map, int *start_x, int *start_y);
void	free_map(char **grid);
void	draw_map(t_game *game);
int		check_path(t_map *map, int sx, int sy);

//vaildate_path.c
int		count_collectibles(t_map *map);

//init_img.c
int		init_graphics(t_game *game);
int		load_image(t_game *game, const char *file, mlx_image_t **img);
/* helper functions implemented in validate_map.c are internal */

#endif

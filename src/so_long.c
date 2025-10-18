/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:55:25 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/18 18:19:52 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			mlx_image_to_window(game->mlx, game->img_floor, x * TILE, y * TILE);
			if (game->map->grid[y][x] == '1')
				mlx_image_to_window(game->mlx, game->img_wall, x * TILE, y * TILE);
			else if (game->map->grid[y][x] == 'E' && game->collectibles == 0)
				mlx_image_to_window(game->mlx, game->img_exit, x * TILE, y * TILE);
			else if (game->map->grid[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->img_collect, x * TILE, y * TILE);
			x++;
		}
		y++;
	}
 	mlx_image_to_window(game->mlx, game->img_player,
						game->player_x * TILE,
						game->player_y * TILE);
}

/* helpers para main: setup, init graphics y run */
static int setup_game(int argc, char **argv, t_game *game)
{
	if (argc != 2 || !check_ber(argv[1]))
		return (printf("Formato: ./so_long <mapa.ber>\n"), 1);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (printf("Error\nmalloc\n"), 1);
	game->map->grid = read_map(argv[1]);
	if (!game->map->grid)
		return (printf("Error: no se pudo leer el mapa\n"), 1);
	game->map->width = strlen(game->map->grid[0]);
	game->map->height = ft_arrlen(game->map->grid);
	game->player_x = 1;
	game->player_y = 1;
	game->moves = 0;
	game->collectibles = 0;
	return (0);
}

static int	init_graphics(t_game *game)
{
	mlx_texture_t	*tex;

	game->mlx = mlx_init(game->map->width * TILE, game->map->height * TILE,
						"so_long", true);
	if (!game->mlx)
		return (printf("Error iniciando MLX\n"), 1);
	tex = mlx_load_png("assets/player.png");
	game->img_player = mlx_texture_to_image(game->mlx, tex);
	tex = mlx_load_png("assets/floor.png");
	game->img_floor = mlx_texture_to_image(game->mlx, tex);
	tex = mlx_load_png("assets/wall.png");
	game->img_wall = mlx_texture_to_image(game->mlx, tex);
	tex = mlx_load_png("assets/exit.png");
	game->img_exit = mlx_texture_to_image(game->mlx, tex);
	tex = mlx_load_png("assets/collectible.png");
	game->img_collect = mlx_texture_to_image(game->mlx, tex);
	return (0);
}

static void	run_game(t_game *game)
{
	int	y;
	int	x;

	/* contar collectibles */
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
			if (game->map->grid[y][x] == 'C')
				game->collectibles++;
	}
	draw_map(game);
	mlx_key_hook(game->mlx, &my_keyhook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_map(game->map->grid);
	free(game->map);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	*map;
	// char **map;

	if (setup_game(argc, argv, &game))
        return (1);
		
	// map = read_map(argv[1]);
	
	// if (!map)
	// 	return (1);
		map = malloc(sizeof(t_map));
	if (!map)
		return (printf("Error\nmalloc\n"), 1);
	map->grid = read_map(argv[1]);
	if (!map->grid)
		return (printf("Error: no se pudo leer el mapa\n"), 1);
	map->width = strlen(map->grid[0]);
	map->height = ft_arrlen(map->grid);

	if (validate_map_full(map, &game.player_x, &game.player_y))
	{
		free_map(game.map->grid);
		free(game.map);
		return (1);
	}
	if (init_graphics(&game))
	{
		free_map(game.map->grid);
		free(game.map);
		return (1);
	}
	run_game(&game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:55:25 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/25 18:15:53 by susanamadri      ###   ########.fr       */
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
				mlx_image_to_window(game->mlx, game->img_wall, x * TILE,
					y * TILE);
			else if (game->map->grid[y][x] == 'E' && game->collectibles == 0)
				mlx_image_to_window(game->mlx, game->img_exit, x * TILE,
					y * TILE);
			else if (game->map->grid[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->img_collect, x * TILE,
					y * TILE);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->img_player,
		game->player_x * TILE, game->player_y * TILE);
}

/* helpers para main: setup, init graphics y run */
static int	setup_game(int argc, char **argv, t_game *game)
{
	if (argc != 2 || !check_ber(argv[1]))
		return (ft_printf("Formato: ./so_long <mapa.ber>\n"), 1);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (ft_printf("Error\nmalloc\n"), 1);
	game->map->grid = read_map(argv[1]);
	if (!game->map->grid)
	{
		free(game->map);
		return (ft_printf("Error: no se pudo leer el mapa\n"), 1);
	}
	game->map->width = ft_strlen(game->map->grid[0]);
	game->map->height = ft_arrlen(game->map->grid);
	game->player_x = 1;
	game->player_y = 1;
	game->moves = 0;
	game->collectibles = 0;
	return (0);
}


void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return;

	// Liberar mapa
	if (game->map)
	{
		if (game->map->grid)
		{
			for (i = 0; i < game->map->height; i++)
				free(game->map->grid[i]);
			free(game->map->grid);
		}
		free(game->map);
		game->map = NULL;
	}

	// Liberar imágenes de MLX42
	if (game->mlx)
	{
		ft_printf("Liberando recursos de MLX42...\n");
		if (game->img_player) mlx_delete_image(game->mlx, game->img_player);
		if (game->img_wall) mlx_delete_image(game->mlx, game->img_wall);
		if (game->img_floor) mlx_delete_image(game->mlx, game->img_floor);
		if (game->img_exit) mlx_delete_image(game->mlx, game->img_exit);
		if (game->img_collect) mlx_delete_image(game->mlx, game->img_collect);

		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}


static void	run_game(t_game *game)
{
	int	y;
	int	x;

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
	free_game(game);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	*map;

	if (setup_game(argc, argv, &game))
		return (1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_printf("Error\nmalloc\n"), 1);
	map->grid = read_map(argv[1]);
	if (!map->grid)
	{
		free(map);
		return (ft_printf("Error: no se pudo leer el mapa\n"), 1);
	}
	map->width = ft_strlen(map->grid[0]);
	map->height = ft_arrlen(map->grid);
	if (validate_map_full(map, &game.player_x, &game.player_y))
		return (free_map(game.map->grid), free(game.map), 1);
	if (init_graphics(&game))
		return (free_map(game.map->grid), free(game.map), 1);
	run_game(&game);
	return (0);
}


/////////////////////////////////////

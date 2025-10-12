/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:51:32 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/12 20:56:06 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	reveal_exits(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->grid[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->img_exit, x * TILE, y * TILE);
			x++;
		}
		y++;
	}
}

static void	handle_collectible(t_game *game, int nx, int ny)
{
	if (game->map->grid[ny][nx] == 'C')
	{
		game->map->grid[ny][nx] = '0';
		game->collectibles--;
		printf("[DEBUG] Coleccionable tomado en (%d,%d). Quedan: %d\n",
			nx, ny, game->collectibles);

		mlx_image_to_window(game->mlx, game->img_floor, nx * TILE, ny * TILE);
		/* si fue el último, mostrar la(s) salida(s) */
		if (game->collectibles == 0)
			reveal_exits(game);
	}
}

static int	handle_exit(t_game *game, int nx, int ny)
{
	if (game->map->grid[ny][nx] == 'E')
	{
		if (game->collectibles == 0)
		{
			printf("¡Ganaste en %d movimientos!\n", game->moves + 1);
			mlx_close_window(game->mlx);
			return (1);
		}
	}
	return (0);
}

static int	can_move_to(t_game *game, int nx, int ny)
{
	char	cell;

	if (ny < 0 || ny >= game->map->height)
		return (0);
	if (nx < 0 || nx >= game->map->width)
		return (0);
	if ((int)strlen(game->map->grid[ny]) <= nx)
		return (0);
	cell = game->map->grid[ny][nx];
	if (cell == '1')
		return (0);
	if (cell == 'C')
		handle_collectible(game, nx, ny);
	if (handle_exit(game, nx, ny))
		return (0);
	return (1);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	nx;
	int	ny;
	int	ox;
	int	oy;

	nx = game->player_x + dx;
	ny = game->player_y + dy;
	ox = game->player_x;
	oy = game->player_y;
	if (!can_move_to(game, nx, ny))
		return ;
	/* redibujar suelo en la posición antigua del jugador */
	mlx_image_to_window(game->mlx, game->img_floor, ox * TILE, oy * TILE);
	game->player_x = nx;
	game->player_y = ny;
	game->moves++;
	printf("Movimientos: %d\n", game->moves);
	/* dibujar jugador en la nueva posición */
	mlx_image_to_window(game->mlx, game->img_player,
		game->player_x * TILE, game->player_y * TILE);
}


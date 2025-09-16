/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:51:32 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/16 18:43:47 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_collectible(t_game *game, int nx, int ny)
{
	if (game->map->grid[ny][nx] == 'C')
	{
		game->map->grid[ny][nx] = '0';
		game->collectibles--;
		printf("Te queda %d collectibles\n", game->collectibles);
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
		else
			printf("Todavía faltan collectibles!\n");
	}
	return (0);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = game->player_x + dx;
	ny = game->player_y + dy;
	if (nx < 0 || ny < 0 || nx >= game->map->width || ny >= game->map->height)
		return ;
	if (game->map->grid[ny][nx] == '1')
		return ;
	handle_collectible(game, nx, ny);
	if (handle_exit(game, nx, ny))
		return ;
	game->player_x = nx;
	game->player_y = ny;
	game->moves++;
	printf("Movimientos: %d\n", game->moves);
	draw_map_render(game);
}

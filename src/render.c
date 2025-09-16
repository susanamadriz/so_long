/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:53:02 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/16 18:53:13 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void draw_tile(t_game *game, int x, int y)
{
    char c = game->map->grid[y][x];

    mlx_image_to_window(game->mlx, game->img_floor, x * TILE, y * TILE);
    if (c == '1')
        mlx_image_to_window(game->mlx, game->img_wall, x * TILE, y * TILE);
    else if (c == 'C')
        mlx_image_to_window(game->mlx, game->img_collect, x * TILE, y * TILE);
    else if (c == 'E' && game->collectibles == 0)
        mlx_image_to_window(game->mlx, game->img_exit, x * TILE, y * TILE);
}

void draw_map_render(t_game *game)
{
    int x, y;

    y = 0;
    while (y < game->map->height)
    {
        x = 0;
        while (x < game->map->width)
        {
            draw_tile(game, x, y);
            x++;
        }
        y++;
    }
    mlx_image_to_window(game->mlx, game->img_player,
        game->player_x * TILE, game->player_y * TILE);
}

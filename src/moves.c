/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:51:32 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/09 17:53:40 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    move_player(t_game *game, int dx, int dy)
{
    int nx = game->player_x + dx;
    int ny = game->player_y + dy;

    if (nx < 0 || ny < 0 || nx >= game->map->width || ny >= game->map->height)
        return;
    if (game->map->grid[ny][nx] == '1') // pared
        return;

    // Si pisa un collectible
    if (game->map->grid[ny][nx] == 'C')
    {
        game->map->grid[ny][nx] = '0'; // lo borra
        game->collectibles--;         // reduce contador
        printf("Te queda %d collectibles\n", game->collectibles);
    }

    // Si pisa la salida
    if (game->map->grid[ny][nx] == 'E')
    {
        if (game->collectibles == 0)
        {
            printf("¡Ganaste en %d movimientos!\n", game->moves + 1);
            mlx_close_window(game->mlx);
            return;
        }
        else
        {
            printf("Todavía faltan collectibles!\n");
            return;
        }
    }

    game->player_x = nx;
    game->player_y = ny;
    game->moves++;
    printf("Movimientos: %d\n", game->moves);

    mlx_delete_image(game->mlx, game->img_player);
    game->img_player = mlx_texture_to_image(game->mlx,
                        mlx_load_png("assets/player.png"));
    mlx_image_to_window(game->mlx, game->img_player,
                        game->player_x * TILE, game->player_y * TILE);

    // Redibujar mapa para eliminar collectibles recogidos y mostrar salida
    draw_map(game);
}


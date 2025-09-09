/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:55:25 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/09 18:31:00 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_map(t_game *game)
{
    int x, y;

    y = 0;
    while (y < game->map->height)
    {
        x = 0;
        while (x < game->map->width)
        {
            // --- Piso ---
            mlx_image_to_window(game->mlx, game->img_floor, x * TILE, y * TILE);

            // --- Pared ---
            if (game->map->grid[y][x] == '1')
                mlx_image_to_window(game->mlx, game->img_wall, x * TILE, y * TILE);

            // --- Salida solo si no hay collectibles ---
            else if (game->map->grid[y][x] == 'E' && game->collectibles == 0)
                mlx_image_to_window(game->mlx, game->img_exit, x * TILE, y * TILE);

            // --- Collectibles ---
            else if (game->map->grid[y][x] == 'C')
                mlx_image_to_window(game->mlx, game->img_collect, x * TILE, y * TILE);

            x++;
        }
        y++;
    }

    // --- Jugador ---
    mlx_image_to_window(game->mlx, game->img_player,
                        game->player_x * TILE,
                        game->player_y * TILE);
}


int main(int argc, char **argv)
{
    t_game          game;
    mlx_texture_t   *tex;
    int             y, x;

    if (argc != 2)
        return (printf("Formato: ./so_long <mapa.ber>\n"), 1);

    game.map = malloc(sizeof(t_map));
    game.map->grid = read_map(argv[1]);
    if (!game.map->grid)
        return (printf("Error: no se pudo leer el mapa\n"), 1);

    game.map->width = strlen(game.map->grid[0]);
    game.map->height = ft_arrlen(game.map->grid);

    game.player_x = 1;
    game.player_y = 1;
    game.moves = 0;
    game.collectibles = 0;

    // Contar todos los collectibles del mapa
    y = -1;
    while (++y < game.map->height)
    {
        x = -1;
        while (++x < game.map->width)
            if (game.map->grid[y][x] == 'C')
                game.collectibles++;
    }

    game.mlx = mlx_init(game.map->width * TILE, game.map->height * TILE, "so_long", true);
    if (!game.mlx)
        return (printf("Error iniciando MLX\n"), 1);

    tex = mlx_load_png("assets/player.png");
    game.img_player = mlx_texture_to_image(game.mlx, tex);

    tex = mlx_load_png("assets/floor.png");
    game.img_floor = mlx_texture_to_image(game.mlx, tex);

    tex = mlx_load_png("assets/wall.png");
    game.img_wall = mlx_texture_to_image(game.mlx, tex);

    tex = mlx_load_png("assets/exit.png");
    game.img_exit = mlx_texture_to_image(game.mlx, tex);

    tex = mlx_load_png("assets/collectible.png");
    game.img_collect = mlx_texture_to_image(game.mlx, tex);

    draw_map(&game);

    // Usamos el hook de teclado
    mlx_key_hook(game.mlx, &my_keyhook, &game);

    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    return (0);
}

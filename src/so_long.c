/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:55:25 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/03 19:39:48 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_map(t_game *game)
{
    int x, y;

    y = -1;
    while (++y < game->map->height)
    {
        x = -1;
        while (++x < game->map->width)
        {
            mlx_image_to_window(game->mlx, game->img_floor, x * TILE, y * TILE);
            if (game->map->grid[y][x] == '1')
                mlx_image_to_window(game->mlx, game->img_wall, x * TILE, y * TILE);
            else if (game->map->grid[y][x] == 'E')
                mlx_image_to_window(game->mlx, game->img_exit, x * TILE, y * TILE);
            else if (game->map->grid[y][x] == 'C')
                mlx_image_to_window(game->mlx, game->img_collect, x * TILE, y * TILE);
        }
    }
    mlx_image_to_window(game->mlx, game->img_player,
        game->player_x * TILE, game->player_y * TILE);
}

void hook(void *param)
{
    t_game  *g = param;
    int     nx = g->player_x;
    int     ny = g->player_y;

    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
        ny--;
    else if (mlx_is_key_down(g->mlx, MLX_KEY_S))
        ny++;
    else if (mlx_is_key_down(g->mlx, MLX_KEY_A))
        nx--;
    else if (mlx_is_key_down(g->mlx, MLX_KEY_D))
        nx++;
    if (nx >= 0 && ny >= 0 && nx < g->map->width && ny < g->map->height
        && g->map->grid[ny][nx] != '1')
    {
        g->player_x = nx;
        g->player_y = ny;
        g->moves++;
        mlx_delete_image(g->mlx, g->img_player);
        g->img_player = mlx_texture_to_image(g->mlx, mlx_load_png("assets/player.png"));
        mlx_image_to_window(g->mlx, g->img_player, g->player_x * TILE, g->player_y * TILE);
    }
    if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(g->mlx);
}

int main(int argc, char **argv)
{
    t_game          game;
    mlx_texture_t   *tex;

    if (argc != 2)
        return (printf("Uso: ./so_long <mapa.ber>\n"), 1);
    game.map = malloc(sizeof(t_map));
    game.map->grid = read_map(argv[1]);
    game.map->width = strlen(game.map->grid[0]);
    game.map->height = ft_arrlen(game.map->grid);
    game.player_x = 1;
    game.player_y = 1;
    game.moves = 0;
    game.mlx = mlx_init(game.map->width * TILE, game.map->height * TILE, "so_long", true);
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
    mlx_loop_hook(game.mlx, &hook, &game);
    mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
    return (0);
}

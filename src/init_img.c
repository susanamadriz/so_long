/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:18:45 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/26 18:19:09 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_image(t_game *game, const char *file, mlx_image_t **img)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(file);
	if (!tex)
		return (ft_printf("Error cargando %s\n", file), 1);
	*img = mlx_texture_to_image(game->mlx, tex);
	mlx_delete_texture(tex);
	return (0);
}

int	init_graphics(t_game *game)
{
	game->mlx = mlx_init(game->map->width * TILE, game->map->height * TILE,
			"so_long", true);
	if (!game->mlx)
		return (ft_printf("Error iniciando MLX\n"), 1);
	if (load_image(game, "assets/player.png", &game->img_player))
		return (1);
	if (load_image(game, "assets/floor.png", &game->img_floor))
		return (1);
	if (load_image(game, "assets/wall.png", &game->img_wall))
		return (1);
	if (load_image(game, "assets/exit.png", &game->img_exit))
		return (1);
	if (load_image(game, "assets/collectible.png", &game->img_collect))
		return (1);
	return (0);
}

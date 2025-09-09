/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:51:11 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/09 18:52:40 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void my_keyhook(mlx_key_data_t keydata, void *param)
{
    t_game *game = param;

    if (keydata.action == MLX_PRESS) // solo al presionar
    {
        if (keydata.key == MLX_KEY_W )
            move_player(game, 0, -1);
        if (keydata.key == MLX_KEY_S)
            move_player(game, 0, 1);
        if (keydata.key == MLX_KEY_A)
            move_player(game, -1, 0);
        if (keydata.key == MLX_KEY_D)
            move_player(game, 1, 0);
        if (keydata.key == MLX_KEY_ESCAPE)
            mlx_close_window(game->mlx);
    }
}


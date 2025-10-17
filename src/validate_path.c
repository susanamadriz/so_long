/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:00:00 by assistant          #+#    #+#             */
/*   Updated: 2025/10/17 12:00:00 by assistant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <string.h>

static void	flood(t_map *m, int x, int y, int *c_reached, int *e_found)
{
    if (x < 0 || y < 0 || x >= m->width || y >= m->height)
        return ;
    if (m->grid[y][x] == '1' || m->grid[y][x] == 'V')
        return ;
    if (m->grid[y][x] == 'C')
        (*c_reached)++;
    if (m->grid[y][x] == 'E')
        (*e_found) = 1;
    m->grid[y][x] = 'V';
    flood(m, x + 1, y, c_reached, e_found);
    flood(m, x - 1, y, c_reached, e_found);
    flood(m, x, y + 1, c_reached, e_found);
    flood(m, x, y - 1, c_reached, e_found);
}

static int	count_collectibles(t_map *map)
{
    int	y;
    int	x;
    int	count;

    y = 0;
    count = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->grid[y][x] == 'C')
                count++;
            x++;
        }
        y++;
    }
    return (count);
}

int	check_path(t_map *map, int sx, int sy)
{
    t_map	tmp;
    int	c_reached;
    int	e_found;
    int	total_c;

    tmp.grid = copy_map(map);
    if (!tmp.grid)
        return (print_error("No se pudo duplicar el mapa"));
    tmp.width = (int)strlen(tmp.grid[0]);
    tmp.height = ft_arrlen(tmp.grid);
    c_reached = 0;
    e_found = 0;
    total_c = count_collectibles(map);
    flood(&tmp, sx, sy, &c_reached, &e_found);
    free_map(tmp.grid);
    if (!e_found)
        return (print_error("No existe camino hasta la salida 'E'."));
    if (c_reached != total_c)
        return (print_error("No todos los collectibles son alcanzables."));
    return (0);
}

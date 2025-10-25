/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:00:00 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/25 16:33:26 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <string.h>

/* res[0] = c_reached, res[1] = e_found */
static void	flood(t_map *m, int x, int y, int *res)
{
	if (x < 0 || y < 0 || x >= m->width || y >= m->height)
		return ;
	if (m->grid[y][x] == '1' || m->grid[y][x] == 'V')
		return ;
	if (m->grid[y][x] == 'C')
		(res[0])++;
	if (m->grid[y][x] == 'E')
		(res[1]) = 1;
	m->grid[y][x] = 'V';
	flood(m, x + 1, y, res);
	flood(m, x - 1, y, res);
	flood(m, x, y + 1, res);
	flood(m, x, y - 1, res);
}

int	count_collectibles(t_map *map)
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
	int		c_reached;
	int		e_found;
	int		total_c;
	int		res[2];

	tmp.grid = copy_map(map);
	if (!tmp.grid)
		return (print_error("No se pudo duplicar el mapa"));
	tmp.width = (int)ft_strlen(tmp.grid[0]);
	tmp.height = ft_arrlen(tmp.grid);
	c_reached = 0;
	e_found = 0;
	total_c = count_collectibles(map);
	res[0] = 0;
	res[1] = 0;
	flood(&tmp, sx, sy, res);
	c_reached = res[0];
	e_found = res[1];
	free_map(tmp.grid);
	if (!e_found)
		return (print_error("No existe camino hasta la salida 'E'."));
	if (c_reached != total_c)
		return (print_error("No todos los collectibles son alcanzables."));
	return (0);
}

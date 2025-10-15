/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:37:25 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/15 21:47:05 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* src/validate_map.c */
#include "so_long.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
static int	check_rectangular(t_map *map)
{
	int		y;
	size_t	w;

	if (map->height == 0)
		return (print_error("Mapa vacío."));
	w = strlen(map->grid[0]);
	y = 0;
	while (y < map->height)
	{
		if (strlen(map->grid[y]) != w)
			return (print_error("Mapa no es rectangular."));
		y++;
	}
	map->width = (int)w;
	return (0);
}


static int	check_borders(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->width)
	{
		if (map->grid[0][x] != '1' || map->grid[map->height - 1][x] != '1')
			return (print_error("Bordes superior o inferior no cerrados."));
		x++;
	}
	y = 1;
	while (y < map->height - 1)
	{
		if (map->grid[y][0] != '1' || map->grid[y][map->width - 1] != '1')
			return (print_error("Bordes laterales no cerrados."));
		y++;
	}
	return (0);
}


static int	check_chars_counts(t_map *m, int *sx, int *sy)
{
	int	y;
	int	x;
	int	p;
	int	e;
	int	c;

	y = -1;
	p = 0;
	e = 0;
	c = 0;
	while (++y < m->height)
	{
		x = -1;
		while (++x < m->width)
		{
			if (m->grid[y][x] == 'P')
			{
				p++;
				*sx = x;
				*sy = y;
			}
			else if (m->grid[y][x] == 'E')
				e++;
			else if (m->grid[y][x] == 'C')
				c++;
			else if (m->grid[y][x] != '0' && m->grid[y][x] != '1')
				return (print_error("Caracter inválido en el mapa."));
		}
	}
	if (p != 1 || e != 1 || c < 1)
		return (print_error("Mapa debe tener 1 'P', 1 'E' y ≥1 'C'."));
	return (0);
}


/* path checking functions moved to src/validate_path.c */



int	validate_map_full(t_map *map, int *start_x, int *start_y)
{
	if (check_rectangular(map))
		return (1);
	if (check_borders(map))
		return (1);
	if (check_chars_counts(map, start_x, start_y))
		return (1);
	if (check_path(map, *start_x, *start_y))
		return (1);
	return (0);
}

/* NOTE: path checking helpers were previously duplicated. Keep minimal
   flood_local implementation here only to preserve compat while
   higher-level canonical implementation may reside in another file. */

static void	flood_local(t_map *m, int x, int y, int *c_reached, int *e_found)
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
	flood_local(m, x + 1, y, c_reached, e_found);
	flood_local(m, x - 1, y, c_reached, e_found);
	flood_local(m, x, y + 1, c_reached, e_found);
	flood_local(m, x, y - 1, c_reached, e_found);
}

int	check_path(t_map *map, int sx, int sy)
{
	t_map	tmp;
	int	c_reached;
	int	e_found;
	int	total_c;
	int	x;
	int	y;

	tmp.grid = copy_map(map);
	if (!tmp.grid)
		return (print_error("No se pudo duplicar el mapa"));
	tmp.width = (int)strlen(tmp.grid[0]);
	tmp.height = ft_arrlen(tmp.grid);
	c_reached = 0;
	e_found = 0;
	total_c = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == 'C')
				total_c++;
			x++;
		}
		y++;
	}
	flood_local(&tmp, sx, sy, &c_reached, &e_found);
	free_map(tmp.grid);
	if (!e_found)
		return (print_error("No existe camino hasta la salida 'E'."));
	if (c_reached != total_c)
		return (print_error("No todos los collectibles son alcanzables."));
	return (0);
}



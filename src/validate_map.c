/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:37:25 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/18 18:13:46 by susanamadri      ###   ########.fr       */
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





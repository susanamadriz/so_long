/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:37:25 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/18 23:44:01 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_rectangular(t_map *map)
{
	int		y;
	size_t	w;

	if (map->height == 0)
		return (print_error("Mapa vacío."));
	w = ft_strlen(map->grid[0]);
	y = 0;
	while (y < map->height)
	{
		if (ft_strlen(map->grid[y]) != w)
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

static int	scan_row_counts(t_map *m, int row, int *sx, int *sy)
{
	int		x;
	char	cell;

	x = 0;
	while (x < m->width)
	{
		cell = m->grid[row][x];
		if (cell == 'P')
		{
			m->p++;
			*sx = x;
			*sy = row;
		}
		else if (cell == 'E')
			m->e++;
		else if (cell == 'C')
			m->c++;
		else if (cell != '0' && cell != '1')
			return (print_error("Caracter inválido en el mapa."));
		x++;
	}
	return (0);
}

static int	check_chars_counts(t_map *m, int *sx, int *sy)
{
	int	y;

	m->p = 0;
	m->e = 0;
	m->c = 0;
	y = 0;
	while (y < m->height)
	{
		if (scan_row_counts(m, y, sx, sy) != 0)
			return (-1);
		y++;
	}
	if (m->p != 1 || m->e != 1 || m->c < 1)
		return (print_error("Mapa debe tener 1 'P', 1 'E' y ≥ 1 'C'."));
	return (0);
}

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

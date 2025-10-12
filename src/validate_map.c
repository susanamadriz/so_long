/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:37:25 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/12 21:26:36 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* src/validate_map.c */
#include "so_long.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	print_error(const char *msg)
{
	printf("Error\n%s\n", msg);
	return (1);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free (map);
}

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
			if (m->grid[y][x] == 'P' && (++p))
				*sx = x, *sy = y;
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


/* Flood Fill recursivo */
static void	flood(t_map *map, int x, int y, int *c_reached, int *e_found)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return ;
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'V')
		return ;
	if (map->grid[y][x] == 'C') (*c_reached)++;
	if (map->grid[y][x] == 'E') (*e_found) = 1;
	map->grid[y][x] = 'V';
	flood(map, x + 1, y, c_reached, e_found);
	flood(map, x - 1, y, c_reached, e_found);
	flood(map, x, y + 1, c_reached, e_found);
	flood(map, x, y - 1, c_reached, e_found);
}
static char **copy_map(t_map *map)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		copy[y] = strdup(map->grid[y]);
		y++;
	}
	copy[map->height] = NULL;
	return (copy);
}

static int check_path(t_map *map, int sx, int sy)
{
	int		c_reached = 0;
	int		e_found = 0;
	int		total_c = 0;
	int		x;
	int		y = 0;
	t_map	*temp_map;

	temp_map = malloc(sizeof(t_map));
	if (!temp_map)
        return (printf("Error\nmalloc\n"), 1);
    temp_map->grid = copy_map(map);
    if (!temp_map->grid)
        return (printf("Error: no se pudo leer el mapa\n"), 1);
    temp_map->width = strlen(temp_map->grid[0]);
    temp_map->height = ft_arrlen(temp_map->grid);

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

    flood(temp_map, sx, sy, &c_reached, &e_found);
    free_map(temp_map->grid);
    if (!e_found)
        return (print_error("No existe camino hasta la salida 'E'."));
    if (c_reached != total_c)
        return (print_error("No todos los collectibles son alcanzables."));
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



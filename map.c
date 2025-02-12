/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:18:45 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/02/08 20:17:25 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// El archivo tiene que estar previamente comporbado
// Leer el mapa original para luego poder modificarlo en cada movimiento
int count_map(char *archivo)
{
	int fd;
	char *line;
	int len;
	
	len = 0;
	fd = open(archivo, O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		len++;
	}
	close (fd);
	return (len);
}
char **read_map(char *archivo)
{
	int fd;
	char **map;
	int i;
	int len;
	char *linea;

	i = 0;
	map = malloc(len + 1 * sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(archivo, O_RDONLY);
	len = count_map(archivo);
	while (i < len)
	{
		linea = get_next_line(fd);
		map[i] = ft_substr(linea, 0, ft_strlen(linea) - 1);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

// VERIFICACION MAPA ##

int char_check(char **map)
{
	int i;
	int y;
	// char *valid;

	// valid = "01CEP";
		
	i = 0;
	y = 0;
	if (!map)
		return(1);
	while (map[i])
	{
		while (map[i][y])
		{
			if (map[i][y] != '0' || map[i][y] != '1' || map[i][y] != 'C' ||
				 map[i][y] != 'E' || map[i][y] != 'P');
				return (1);
			y++;
		}
		i++;
	}
	return (0);
}

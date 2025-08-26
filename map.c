/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:18:45 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/08/26 19:58:57 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// ------------------------------------------------------------
// Cuenta cuántas líneas tiene el archivo (cantidad de filas)
// ------------------------------------------------------------
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
		free(line);
	}
	close (fd);
	return (len);
}
// ------------------------------------------------------------
// Lee el archivo .ber y lo guarda en un char **
// ------------------------------------------------------------
static char	*clean_line(char *linea)
{
	int	l;

	if (!linea)
		return (NULL);
	l = ft_strlen(linea);
	if (l > 0 && linea[l - 1] == '\n')
		return (ft_substr(linea, 0, l - 1));
	return (ft_strdup(linea));
}
char	**read_map(char *archivo)
{
	int		fd;
	int		i;
	int		len;
	char	*linea;
	char	**map;

	len = count_map(archivo);
	if (len <= 0)
		return (NULL);
	map = malloc((len + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(archivo, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = 0;
	linea = get_next_line(fd);
	while (linea)
	{
		map[i++] = clean_line(linea);
		free(linea);
		linea = get_next_line(fd);
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
int square_check(char **map)
{
	int i;
	int y;
	int len;

	i = 0;
	y = 0;
	len = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != len)
			return (1);
		i++;
	}
	return (0);
}

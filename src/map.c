/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:18:45 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/11 23:44:47 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	char_check(char **map)
{
	int	i;
	int	y;

	i = 0;
	if (!map)
		return (1);
	while (map[i])
	{
		y = 0;
		while (map[i][y])
		{
			if (map[i][y] != '0' && map[i][y] != '1' && map[i][y] != 'C' &&
				map[i][y] != 'E' && map[i][y] != 'P')
				return (1);
			y++;
		}
		i++;
	}
	return (0);
}

static char	*ignore_empty(char *line)
{
	int	len;
	int	start;

	start = 0;
	len = strlen(line);
	if (!line)
		return (NULL);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	while (line[start] && (line[start] == ' ' || line[start] == '\t'))
		start++;
	if (line[start] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line + start);
}


int	count_map(char *file)
{
	int		fd;
	int		len;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	len = 0;
	while ((line = get_next_line(fd)))
	{
		if (ignore_empty(line))
			len++;
	}
	close(fd);
	return (len);
}

char	**read_map(char *file)
{
	int		fd;
	char	**map;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (count_map(file) + 1));
	if (!map)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		line = ignore_empty(line);
		if (line)
			map[i++] = line;
	}
	close(fd);
	map[i] = NULL;
	if (i == 0)
		return (free(map), NULL);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:18:45 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/10 18:58:42 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int count_map(char *file)
{
	int fd;
	int len;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	len = 0;
	close(fd);
	return (len);
}

char **read_map(char *file)
{
	int fd;
	char **map;
	char *line;
	int i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (count_map(file) + 1));
	if (!map)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (line)
			map[i++] = line;
	}
	close(fd);
	map[i] = NULL;
	if (i == 0)
		return (free(map), NULL);
	return (map);
}

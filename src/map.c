/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:18:45 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/09 18:22:56 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

int count_map(char *file)
{
    int     fd;
    int     len;
    char    *line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    len = 0;
    line = get_next_line(fd);
    while (line)
    {
        len++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (len);
}

static char *clean_line(char *line)
{
    int l;

    if (!line)
        return (NULL);
    l = strlen(line);
    if (l > 0 && line[l - 1] == '\n')
        line[l - 1] = '\0';
    return (line);
}

char **read_map(char *file)
{
    int     fd;
    int     i;
    int     len;
    char    *line;
    char    **map;

    len = count_map(file);
    if (len <= 0)
        return (NULL);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (NULL);
    map = malloc((len + 1) * sizeof(char *));
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        map[i++] = clean_line(line);
        line = get_next_line(fd);
    }
    map[i] = NULL;
    close(fd);
    return (map);
}
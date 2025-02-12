/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:02:33 by sjuan-ma          #+#    #+#             */
/*   Updated: 2024/11/26 10:50:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*pointer;

	total_size = count * size;
	if (size != 0 && total_size >= SIZE_MAX)
		return (NULL);
	pointer = malloc(total_size);
	if (pointer == NULL)
		return (NULL);
	while (total_size > 0)
	{
		pointer[total_size - 1] = 0;
		total_size--;
	}
	return (pointer);
}

char	*more_info(char *save, int fd)
{
	ssize_t	bytes_read;
	char	*buf;
	char	*aux;
	char	*raw;

	raw = ft_substr(save, 0, ft_strlen(save));
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(raw, '\n'))
	{
		buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		if (!buf)
			return (free (raw), NULL);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buf), free(raw), NULL);
		aux = raw;
		raw = ft_strjoin(aux, buf);
		free(aux);
		free(buf);
	}
	return (raw);
}

char	*cut_line(char *raw)
{
	char	*result;

	if (raw && ft_strchr(raw, '\n'))
		result = ft_substr(raw, 0, (ft_strlen(raw)
					- ft_strlen(ft_strchr(raw, '\n') + 1)));
	else
		result = ft_strdup(raw);
	return (result);
}

char	*update_save(char *raw)
{
	char	*save;
	char	*aux;

	aux = ft_strchr(raw, '\n');
	if (aux)
		save = ft_substr(aux, 1, ft_strlen(aux));
	else
		return (NULL);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*newstr;
	char		*raw;
	static char	*save[__FD_SETSIZE];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > __FD_SETSIZE)
		return (NULL);
	raw = more_info(save[fd], fd);
	free (save[fd]);
	save[fd] = NULL;
	if (!raw)
		return (NULL);
	if (raw[0] == '\0')
		return (free(raw), NULL);
	newstr = cut_line(raw);
	if (!newstr)
		return (free(raw), NULL);
	save[fd] = update_save(raw);
	free (raw);
	return (newstr);
}
// int main (int argc, char **argv)
// {
// 	int fd;
// 	char *line;
// 	int i = 0;

// 	fd = open(argv[1], O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("½s\n", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }

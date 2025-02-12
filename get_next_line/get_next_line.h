/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:02:33 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/02/08 19:07:04 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdio.h> 
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500000
# endif

void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

char	*get_next_line(int fd);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:54:52 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/09/26 17:02:49 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_arrlen(char **arr)
{
    int i;

    i = 0;
    if (!arr)
        return (0);
    while (arr[i])
        i++;
    return (i);
}
int check_ber(const char *filename)
{
    int len;

    if (!filename)
        return (0);
    len = 0;
    while (filename[len])
        len++;
    if (len < 4)
        return (0);
    if (filename[len - 1] != 'r' || filename[len - 2] != 'e'
        || filename[len - 3] != 'b' || filename[len - 4] != '.')
        return (0);
    return (1);
}

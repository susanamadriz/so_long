/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:08:42 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/18 21:25:19 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*z;
	size_t			count;

	if (!s || n == 0)
		return;
	z = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		z[count] = 0;
		count++;
	}
}

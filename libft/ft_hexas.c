/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:59:54 by sjuan-ma          #+#    #+#             */
/*   Updated: 2024/10/02 11:56:11 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexa_min(unsigned int x)
{
	int	i;

	i = 0;
	if (x >= 16)
	{
		i += ft_hexa_min(x / 16);
		i += ft_hexa_min(x % 16);
	}
	else
	{
		if (x < 10)
			i += ft_putchar(x + 48);
		else
			i += ft_putchar(x - 10 + 'a');
	}
	return (i);
}

int	ft_hexa_mayus(unsigned int X)
{
	int	i;

	i = 0;
	if (X >= 16)
	{
		i += ft_hexa_mayus(X / 16);
		i += ft_hexa_mayus(X % 16);
	}
	else
	{
		if (X < 10)
			i += ft_putchar(X + 48);
		else
			i += ft_putchar(X - 10 + 'A');
	}
	return (i);
}

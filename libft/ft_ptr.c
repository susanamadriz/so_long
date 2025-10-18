/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:03:14 by sjuan-ma          #+#    #+#             */
/*   Updated: 2024/10/02 12:18:55 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_ptr(void *ptr)
{
	unsigned long	address;
	int				i;

	i = 0;
	address = (unsigned long)ptr;
	if (address == 0)
		return (i += ft_putstr("(nil)"), i);
	i += write(1, "0x", 2);
	i += ft_hexa_min_ptr(address);
	return (i);
}

int	ft_hexa_min_ptr(unsigned long x)
{
	int	i;

	i = 0;
	if (x >= 16)
	{
		i += ft_hexa_min_ptr(x / 16);
		i += ft_hexa_min_ptr(x % 16);
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

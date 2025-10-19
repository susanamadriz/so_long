/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:52:49 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/18 21:53:30 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		if (-2147483648 == n)
		{
			i += ft_putstr("-2147483648");
			return (11);
		}
		n = n * -1;
		i += write(1, "-", 1);
	}
	if (n == 0)
		i += write(1, "0", 1);
	else if (n > 0 && n < 10)
		i += ft_putchar((n + 48));
	else
	{
		i += ft_putnbr((n / 10));
		i += ft_putchar((n % 10) + 48);
	}
	return (i);
}

int	ft_putunbr(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i += write(1, "0", 1);
	else if (n > 0 && n < 10)
		i += ft_putchar((n + 48));
	else
	{
		i += ft_putnbr((n / 10));
		i += ft_putchar((n % 10) + 48);
	}
	return (i);
}

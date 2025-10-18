/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuan-ma <sjuan-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:18:40 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/03/17 16:49:42 by sjuan-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_letter(char letter, va_list args)
{
	int	i;

	i = 0;
	if (letter == '%')
		i += ft_putchar('%');
	else if (letter == 'c')
		i += ft_putchar(va_arg(args, int));
	else if (letter == 's')
		i += ft_putstr(va_arg(args, char *));
	else if (letter == 'd' || letter == 'i')
		i += ft_putnbr(va_arg(args, int));
	else if (letter == 'u')
		i += ft_putunbr(va_arg(args, unsigned long));
	else if (letter == 'p')
		i += ft_put_ptr(va_arg(args, void *));
	else if (letter == 'x')
		i += ft_hexa_min(va_arg(args, unsigned int));
	else if (letter == 'X')
		i += ft_hexa_mayus(va_arg(args, unsigned int));
	return (i);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += check_letter(str[i], args);
		}
		else
		{
			len += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(args);
	return (len);
}
// int main()
// {
// 	int	prueba = -12345;
// 	ft_printf("No tengo %u", prueba);
// 	return (0);
// }

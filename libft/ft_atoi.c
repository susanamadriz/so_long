/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:59:30 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/18 21:27:19 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	conversion;

	i = 0;
	sign = 1;
	conversion = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		conversion = conversion * 10 + (str[i] - '0');
		i++;
	}
	return (conversion * sign);
}

/* {
int main()
	char hola[] = "-211";
	int result;

	result = ft_atoi(hola);
	printf("%d", result);
	return (0);
} */
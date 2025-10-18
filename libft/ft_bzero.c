/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susanamadriz <susanamadriz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:08:42 by sjuan-ma          #+#    #+#             */
/*   Updated: 2025/10/18 18:33:47 by susanamadri      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	ft_bzero(void *s, size_t n)
{
	unsigned char	*z;
	size_t			count;

	z = s;
	count = 0;
	if (n == 0)
		return (*s);
	while (count < n)
	{
		z[count] = 0;
		count++;
	}
}

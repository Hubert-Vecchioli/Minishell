/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:49:47 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 23:43:33 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_size(long nb)
{
	int	size;

	size = 1;
	if (nb < 0)
	{
		nb *= -1;
		size++;
	}
	while ((nb / 10) > 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		res_size;

	n = nb;
	res_size = int_size(n);
	str = malloc((res_size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[res_size--] = 0;
	if (n == 0)
		str[0] = 48;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[res_size] = 48 + (n % 10);
		n /= 10;
		res_size--;
	}
	return (str);
}

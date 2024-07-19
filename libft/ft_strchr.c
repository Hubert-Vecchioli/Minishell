/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:57:49 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/18 12:37:47 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int to_find)
{
	int	i;

	i = 0;
	while (str[i] != (char)to_find)
	{
		if (!str[i])
			return ((char *) 0);
		i++;
	}
	return ((char *) &str[i]);
}

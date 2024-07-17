/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:27:57 by hvecchio          #+#    #+#             */
/*   Updated: 2024/05/20 00:58:42 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int to_find)
{
	size_t	i;

	i = ft_strlen(str);
	while (str[i] != (char)to_find)
	{
		if (str[i] != to_find && !i)
			return ((char *) 0);
		i--;
	}
	return ((char *) &str[i]);
}

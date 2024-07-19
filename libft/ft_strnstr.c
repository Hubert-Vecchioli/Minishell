/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:46:57 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/18 15:11:50 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	if ((!str || !to_find) && !n)
		return (NULL);
	if (!*to_find)
		return ((char *)str);
	i = 0;
	while (str[i] && i < n)
	{
		j = 0;
		while (str[i + j] && to_find[j] && str[i + j] == to_find[j]
			&& i + j < n)
			j++;
		if (!to_find[j])
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:31:03 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/10 17:31:35 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr_end(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	if ((str == NULL || to_find == NULL) && !n)
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
			return ((char *)(str + i + j));
		i++;
	}
	return (NULL);
}
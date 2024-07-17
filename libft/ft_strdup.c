/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:56:15 by hvecchio          #+#    #+#             */
/*   Updated: 2024/05/19 22:40:20 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy_str;
	int		i;

	copy_str = (malloc((ft_strlen(src) + 1) * sizeof(char)));
	if (copy_str == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy_str[i] = src[i];
		i++;
	}
	copy_str[i] = 0;
	return (copy_str);
}

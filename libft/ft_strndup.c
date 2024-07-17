/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:19:55 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/10 17:57:21 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int wordlen)
{
	char	*copy_str;
	int		i;

	copy_str = ft_calloc((wordlen + 1), sizeof(char));
	if (copy_str == NULL)
		return (0);
	i = 0;
	while (src[i] && i < wordlen)
	{
		copy_str[i] = src[i];
		i++;
	}
	while (i <= wordlen)
	{
		copy_str[i] = 0;
		i++;
	}
	return (copy_str);
}
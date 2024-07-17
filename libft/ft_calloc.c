/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:41:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/05/20 11:46:07 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*result;

	if (size != 0 && n > (size_t) - 1 / size)
		return (NULL);
	result = malloc(n * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, (n * size));
	return (result);
}

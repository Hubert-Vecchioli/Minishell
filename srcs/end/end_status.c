/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:33:12 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/18 17:00:30 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_end(int mode, int end)
{
	static int	last_end = 0;

	if (mode == 1)
		last_end = end;
	return (last_end);
}

int	ft_get_end(void)
{
	return (ft_end(0, 0));
}

void	ft_set_end(int end)
{
	ft_end(1, end);
	return ;
}

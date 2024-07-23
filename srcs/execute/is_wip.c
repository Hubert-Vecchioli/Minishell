/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:47:08 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 18:54:40 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_status_wip(int mode, int status)
{
	static int	last_status_wip = 0;

	if (mode == 1)
		last_status_wip = status;
	return (last_status_wip);
}

int	ft_get_wip(void)
{
	return (ft_status_wip(0, 0));
}

void	ft_set_wip(int status)
{
	ft_status_wip(1, status);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:08:16 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 00:14:55 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_status(int mode, int status)
{
	static int	last_status = 0;

	if (mode == 1)
		last_status = status;
	return (last_status);
}

int	ft_get_status(void)
{
	return (ft_status(0, 0));
}

void	ft_set_status(int status)
{
	ft_status(1, status);
	return ;
}

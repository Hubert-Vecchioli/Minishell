/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:50:24 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/22 10:50:41 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int ac, char **av, int status, t_list **env)
{
	(void) ac;
	(void) env;
	(void) av;
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_set_end(1);
	return(status);
}

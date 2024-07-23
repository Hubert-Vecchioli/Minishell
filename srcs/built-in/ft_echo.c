/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:59:49 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 11:56:03 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//documentation: https://pubs.opengroup.org/onlinepubs/009695399/utilities/echo.html

static int	ft_has_n_flag( char *arg)
{
	int	i;

	i = 1;
	if (arg && arg[0] == '-')
	{
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_echo(int ac, char **av)
{
	int	has_n_flag;

	has_n_flag = 0;
	ac--;
	av++;
	while (ac > 0 && ft_has_n_flag(*av))
	{
		if (ft_strchr(*av, 'n'))
			has_n_flag = 1;
		ac--;
		av++;
	}
	while (ac > 0)
	{
		ft_putstr_fd(*av, STDOUT_FILENO);
		if (ac > 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ac--;
		av++;
	}
	if (!has_n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

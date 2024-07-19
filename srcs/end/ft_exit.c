/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:50:24 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/18 17:00:18 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strisnum(char *str)
{
	if (!str)
		return (0);
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		str++;
	while (ft_iswhitespace(*str))
		str++;
	if (*str)
		return (0);
	return (1);
}

int	ft_exit(int ac, char **av, int status)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_set_end(1);
	if (ac == 1)
		return (status);
	else if (!ft_strisnum(av[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (1);
	}
	else if (ac <= 2)
		return (ft_atoi(av[1]));
	else
	{
		ft_set_end(0);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
}

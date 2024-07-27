/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:50:24 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/26 12:53:50 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	arg_check_eq2(char **av)
{
	if (ft_isnumber(av[1]))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_set_end(1);
		return ((unsigned char)(ft_atoi(av[1])));
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(av[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ft_set_end(1);
		return (2);
	}
}

static int	arg_check_sup2(char **av)
{
	if (ft_isnumber(av[1]))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		ft_set_end(0);
		return (1);
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(av[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ft_set_end(1);
		return (2);
	}
}

int	ft_exit(int ac, char **av, int status, t_list **env)
{
	(void) env;
	if (ac == 2)
		return (arg_check_eq2(av));
	else if (ac > 2)
		return (arg_check_sup2(av));
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_set_end(1);
	return (status);
}

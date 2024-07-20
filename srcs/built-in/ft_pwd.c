/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:30:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 04:17:19 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int ac, char **av)
{
	(void) ac;
	(void) av;
	char	*pwd;

	pwd = (char [1024]){0};
	pwd = getcwd(pwd, 1024);
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
	}
	else
	{
		perror("Minishell: pwd: error retrieving current directory: getcwd: cannot access directory");
	}
	return (0);
}

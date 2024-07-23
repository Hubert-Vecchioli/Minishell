/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:30:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 15:02:37 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int ac, char **av)
{
	char	*pwd;

	(void) ac;
	(void) av;
	pwd = (char [1024]){0};
	pwd = getcwd(pwd, 1024);
	if (pwd)
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
	}
	else
	{
		perror("minishell: pwd: error retrieving current directory:\
 getcwd: cannot access directory");
	}
	return (0);
}

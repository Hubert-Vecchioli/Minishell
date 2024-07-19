/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:30:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 00:13:24 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_option(const char *option, char *arg)
{
	if (arg[0] != '-' || !arg[1])
		return (0);
	arg++;
	while (*arg)
	{
		if (!ft_strchr(arg, *option))
			return (0);
		arg++;
	}
	return (1);
}

char	*ft_getcwd(void)
{
	char	*buf;
	size_t	size;

	size = 1;
	buf = malloc(size);
	if (!buf)
		return (NULL);
	while (!getcwd(buf, size))
	{
		if (errno != ERANGE)
		{
			free(buf);
			return (NULL);
		}
		else if (size == 0)
		{
			free(buf);
			return (NULL);
		}
		size *= 2;
		buf = (char *)ft_realloc(buf, size);
		if (!buf)
			return (NULL);
	}
	return (buf);
}

int	ft_pwd(int ac, char **av)
{
	char	*buf;

	while (ac > 0 && valid_option("LP", *av))
	{
		ac--;
		av++;
	}
	buf = ft_getcwd();
	if (!buf)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putendl_fd(buf, STDOUT_FILENO);
	free(buf);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:51:39 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 10:58:25 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rmv_dotdot(char *path)
{
	size_t	j;

	j = 0;
	while (path[j])
	{
		if (!ft_strncmp("../", path + j, 3)
			|| !ft_strcmp("..", path + j))
		{
			path[j + 1] = '/';
			path[j] = '/';
			while (j && path[j] == '/')
				j--;
			while (j && path[j] != '/')
				path[j--] = '/';
		}
		else
			j++;
	}
}


static void	ft_rmv_dot(char *path)
{
	char	*new_path;
	size_t	i;
	size_t	j;

	new_path = (char [PATH_MAX]){0};
	i = 0;
	j = 0;
	while (j < PATH_MAX && path[i])
	{
		if (!i && path[i] == '/')
			new_path[j++] = path[i++];
		else if (path[i] == '/')
		{
			new_path[j++] = path[i++];
			while (path[i] == '/')
				i++;
		}
		else if (!ft_strncmp("./", path + i, 2)
			|| !ft_strcmp(".", path + i))
			i++;
		else
			while (path[i] && path[i] != '/')
				new_path[j++] = path[i++];
	}
	ft_strlcpy(path, new_path, PATH_MAX);
}

static void	ft_rmv_slash(char *path)
{
	int	i;

	i = 1;
	while (path[i])
		i++;
	i--;
	while (i && path[i] == '/')
		path[i--] = 0;
}

static void	ft_rmv_dbl_slash(char *path)
{
	size_t	i;
	size_t	nbslash;

	i = 0;
	while (path[i])
	{
		nbslash = 0;
		while (path[i + nbslash] == '/')
			nbslash++;
		if (nbslash > 1)
			ft_strlcpy(path + i, path + i + nbslash - 1, PATH_MAX - i);
		i++;
		while (path[i] && path[i] != '/')
			i++;
	}
}

char	*ft_realpath(const char *path, char *r_path)
{
	char	*n_path;
	char	*pwd;

	if (!path || !r_path)
		return (NULL);
	n_path = (char [PATH_MAX]){0};
	pwd = (char [1024]){0};
	if (path[0] != '/')
	{
		pwd = getcwd(pwd, 1024);
		ft_strlcpy(n_path, pwd, PATH_MAX);
		ft_strlcat(n_path, "/", PATH_MAX);
	}
	ft_strlcat(n_path, path, PATH_MAX);
	ft_rmv_dot(n_path);
	ft_rmv_dotdot(n_path);
	ft_rmv_dbl_slash(n_path);
	ft_rmv_slash(n_path);
	ft_strlcpy(r_path, n_path, PATH_MAX);
	return (r_path);
}

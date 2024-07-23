/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:28:42 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 15:05:59 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_path(char *path)
{
	int	nb;

	nb = 0;
	if (!path)
		return (0);
	if (*path)
		nb++;
	while (*path)
	{
		if (*path == ':')
			nb++;
		path++;
	}
	return (nb);
}

static char	*ft_get_subpath(char *path, int *j)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (path[*j + i] && path[*j + i] != ':')
		i++;
	ret = malloc(sizeof(char) * (i + 2));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, path + *j, i + 1);
	ret[i] = '/';
	ret[i + 1] = 0;
	*j = *j + i + 1;
	return (ret);
}

static char	**ft_split_path(char *path)
{
	char	**spath;
	int		nbpath;
	int		i;
	int		j;

	nbpath = ft_count_path(path);
	spath = malloc(sizeof(char *) * (nbpath + 1));
	i = 0;
	j = 0;
	if (!spath)
		return (NULL);
	while (i < nbpath)
	{
		spath[i] = ft_get_subpath(path, &j);
		if (!spath[i])
		{
			ft_free_split(&spath);
			return (NULL);
		}
		i++;
	}
	spath[i] = 0;
	return (spath);
}

char	*ft_find_path(char *path, char *key)
{
	char		**spath;
	char		*tpath;
	struct stat	buf;
	int			i;

	spath = ft_split_path(path);
	tpath = NULL;
	i = 0;
	if (!spath)
		return (NULL);
	while (spath[i])
	{
		tpath = ft_strjoin(spath[i], key);
		if (!tpath || stat(tpath, &buf) == 0)
		{
			ft_free_split(&spath);
			return (tpath);
		}
		free(tpath);
		i++;
	}
	ft_free_split(&spath);
	return (ft_strdup(key));
}

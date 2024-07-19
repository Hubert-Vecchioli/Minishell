/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:28:42 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/18 17:01:05 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_spath(char ***spath)
{
	int	i;

	i = 0;
	if (!*spath)
		return ;
	while ((*spath)[i])
	{
		free((*spath)[i]);
		(*spath)[i] = NULL;
		i++;
	}
	free(*spath);
	*spath = NULL;
}

static size_t	nb_spath(char *path)
{
	size_t	nb;

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

static char	*subpath(char *path, size_t *j)
{
	char	*ret;
	size_t	i;

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

static char	**split_path(char *path)
{
	char	**spath;
	size_t	nbpath;
	size_t	i;
	size_t	j;

	nbpath = nb_spath(path);
	spath = malloc(sizeof(char *) * (nbpath + 1));
	i = 0;
	j = 0;
	if (!spath)
		return (NULL);
	while (i < nbpath)
	{
		spath[i] = subpath(path, &j);
		if (!spath[i])
		{
			free_spath(&spath);
			return (NULL);
		}
		i++;
	}
	spath[i] = NULL;
	return (spath);
}

char	*solve_path(char *path, char *key)
{
	char		**spath;
	char		*tpath;
	struct stat	buf;
	int			i;

	spath = split_path(path);
	tpath = NULL;
	i = 0;
	if (!spath)
		return (NULL);
	while (spath[i])
	{
		tpath = ft_strjoin(spath[i], key);
		if (!tpath || stat(tpath, &buf) == 0)
		{
			free_spath(&spath);
			return (tpath);
		}
		free(tpath);
		i++;
	}
	free_spath(&spath);
	return (ft_strdup(key));
}

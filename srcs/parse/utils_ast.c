/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:30:54 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 11:04:58 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	argsize(t_arg *arg)
{
	size_t	ret;

	ret = 0;
	while (arg)
	{
		ret++;
		arg = arg->next;
	}
	return (ret);
}

char	**arg_to_tab(t_arg *arg)
{
	char	**ret;
	size_t	size;
	size_t	i;

	size = argsize(arg);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = ft_strdup(arg->arg);
		if (!ret[i])
		{
			ft_free_split(&ret);
			return (NULL);
		}
		arg = arg->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	tabsize(char **tab)
{
	int	size;

	size = 0;
	if (!tab)
		return (0);
	while (tab[size])
		size++;
	return (size);
}

int	is_redirect(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (INPUT);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	else if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND);
	else
		return (NONE);
}

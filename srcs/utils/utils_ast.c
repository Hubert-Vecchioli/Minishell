/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:30:54 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/26 01:58:12 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_arglen(t_arg *arg)
{
	int	ret;

	ret = 0;
	while (arg)
	{
		ret++;
		arg = arg->next;
	}
	return (ret);
}

char	**ft_split_arg(t_arg *arg)
{
	char	**tab;
	int		length;
	int		i;

	length = ft_arglen(arg);
	tab = malloc(sizeof(char *) * (length + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < length)
	{
		tab[i] = ft_strdup(arg->arg);
		if (!tab[i])
		{
			ft_free_split(&tab);
			return (NULL);
		}
		arg = arg->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	ft_is_redirection(char *str)
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

int	ft_is_path_allowed(char *tab)
{
	struct stat	sb;
	char		*error_msg;

	if (stat(tab, &sb) == 0 && access(tab, X_OK) != 0)
	{
		error_msg = ft_three_strjoin("minishell: ", tab,
				": permission denied");
		ft_putendl_fd(error_msg, 2);
		free(error_msg);
		return (126);
	}
	else
	{
		error_msg = ft_three_strjoin("minishell: ", tab,
				": command not found");
		ft_putendl_fd(error_msg, 2);
		free(error_msg);
		return (127);
	}
}

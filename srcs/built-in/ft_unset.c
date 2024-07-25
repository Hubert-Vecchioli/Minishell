/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:05:21 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/25 12:45:33 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strncmp_env(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < (n - 1))
	{
		i++;
	}
	if (str2[i + 1] == '=')
		return (0);
	return (1);
}

int	ft_is_var_in_env(char *key, t_list **lst_env)
{
	t_list	*temp;
	t_list	*prev;

	temp = *lst_env;
	prev = NULL;
	if (!*lst_env)
		return (0);
	if (temp && !ft_strncmp_env(key, temp->content, ft_strlen(key)))
	{
		*lst_env = temp->next;
		return (free(temp->content), free(temp), 1);
	}
	while (temp)
	{
		prev = temp;
		temp = temp->next;
		if (temp && !ft_strncmp_env(key, temp->content, ft_strlen(key)))
		{
			prev->next = temp->next;
			return (free(temp->content), free(temp), 1);
		}
	}
	return (0);
}

int	ft_unset(int ac, char **av, t_list **env)
{
	(void) ac;
	av++;
	while (*av)
	{
		ft_is_var_in_env(*av, env);
		av++;
	}
	return (0);
}

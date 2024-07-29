/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 01:31:39 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/29 11:27:05 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv_value(char *key, t_list *lst_env)
{
	while (lst_env)
	{
		if (!ft_strncmp(key, lst_env->content, ft_strlen(key))
			&& ((char*)lst_env->content)[ft_strlen(key)] == '=')
			return (ft_strdup((char *)lst_env->content + ft_strlen(key) + 1));
		lst_env = lst_env->next;
	}
	return (NULL);
}

int	ft_is_env_var(char *key, t_list *lst_env)
{
	while (lst_env)
	{
		if (!ft_strncmp(key, lst_env->content, ft_strlen(key))
			&& (((char*)lst_env->content)[ft_strlen(key)] == '='
			|| !((char*)lst_env->content)[ft_strlen(key)]))
			return (1);
		lst_env = lst_env->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:43:08 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 17:40:58 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_convert_lst_to_tab(t_list *lst_env)
{
	size_t	size_env;
	size_t	i;
	char	**env;

	i = 0;
	size_env = ft_lstsize(lst_env);
	env = malloc((size_env + 1) * sizeof(char *));
	while (size_env > i)
	{
		env[i] = ft_strdup((char *)lst_env->content);
		// MALLOC PROTECTION IS MISSING
		i++;
		lst_env = lst_env->next;
	}
	env[i] = NULL;
	return (env);
}

char	*ft_getenv(char *key, t_list *lst_env)
{
	while (lst_env)
	{
		if (!ft_strncmp(key, lst_env->content, ft_strlen(key)))
			return (ft_strdup((char *)lst_env->content + ft_strlen(key)));
			//MALLOC PROTECTION IS MISSING
		lst_env = lst_env->next;
	}
	return (NULL);
}

void	ft_setenv(char *key, char *value, t_list **lst_env)
{
	t_list	*env;
	t_list	*new_node;
	char	*new_keyvalue;

	env = *lst_env;
	new_keyvalue = ft_strjoin(key, value);
	if (!new_keyvalue)
		return ;
	while (env)
	{
		if (!ft_strncmp(key, env->content, ft_strlen(key)))
		{
			free(env->content);
			env->content = new_keyvalue;
			return ;
		}
		env = env->next;
	}
	new_node = ft_lstnew(new_keyvalue);
	if (!new_node)
	{
		free(new_keyvalue);
		return ;
	}
	ft_lstadd_back(lst_env, ft_lstnew(new_keyvalue));
}

void	ft_free_split(char ***split)
{
	int	i;

	i = 0;
	if (*split)
	{
		while ((*split) && (*split)[i])
		{
			free((*split)[i]);
			i++;
		}
		free((*split));
	}
}

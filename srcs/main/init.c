/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:44:13 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/29 13:35:50 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minimal_env(t_list **list_env)
{
	t_list	*new_node;
	char	*new_content;

	new_content = ft_strdup("SHLVL=1");
	if (!new_content)
		return ;
	new_node = ft_lstnew(new_content);
	if (!new_node)
	{
		free(new_content);
		new_content = NULL;
		return ;
	}
	ft_lstadd_back(list_env, new_node);
}

t_list	*ft_init_env(char **env)
{
	t_list	*list_env;
	t_list	*new_node;
	char	*new_content;

	list_env = NULL;
	if (!*env)
		minimal_env(&list_env);
	while (*env)
	{
		new_content = ft_strdup(*env);
		new_node = ft_lstnew(new_content);
		if (!new_node || !new_content)
		{
			free(new_content);
			free(new_node);
			ft_clean_env(&list_env);
			return (NULL);
		}
		ft_lstadd_back(&list_env, new_node);
		env++;
	}
	return (list_env);
}

int	ft_intern_init(t_prompt *prompt, char **env, t_list **lst_env)
{
	signal(SIGINT, ft_clean_prompt);
	signal(SIGQUIT, SIG_IGN);
	prompt->user = getenv("USER");
	*lst_env = ft_init_env(env);
	if (!*lst_env)
	{
		perror("minishell: init_env");
		return (1);
	}
	return (0);
}

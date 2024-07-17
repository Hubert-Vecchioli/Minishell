/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:09:02 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:28:02 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_back(t_master_shell *master_data, t_env *new_elem)
{	
	if (master_data->env_head == NULL)
	{
		master_data->env_head = new_elem;

	}
	else
	{
		ft_lst_last(master_data->env_head)->next = new_elem;
	}
}

t_env	*ft_new_lst(t_master_shell *master_data, char *var_name, char *content)
{
	t_env	*env_var;

	env_var = malloc(sizeof(t_env));
	if (!env_var)
		return (ft_free(master_data), ft_exit(), NULL); // TO REVIEW HOW TO EXIT
	env_var->var_name = ft_strdup(var_name);
	if (!env_var->var_name)						// TO REVIEW HOW TO EXIT
		return (ft_free(master_data), ft_exit(), NULL);
	env_var->content = ft_strdup(content); 
	if (!env_var->content)					// TO REVIEW HOW TO EXIT
		return (ft_free(master_data), ft_exit(), NULL);
	env_var->next = NULL;
	return (env_var);
}

t_env	*ft_lst_last(t_env *env_vars)
{
	t_env	*temp;
	
	temp = env_vars;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

t_env	*ft_lst_find_env_var(t_env *env_vars, char *target_var_name)
{
	t_env	*temp;

	if (!env_vars)
		return (NULL);
	temp = env_vars;
	while (temp)
	{
		if (ft_strcmp(temp->var_name, target_var_name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:50:03 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 11:46:01 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// attention aux doublon

static char	ft_has_special_char(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '*' || str[0] == '$' || str[0] == '?'
		|| str[0] == '#' || str[0] == '-' || str[0] == '!' || str[0] == '@'
		|| ft_isdigit(str[0]))
		return (str[0]);
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '$' || str[i] == '?'
		|| str[i] == '#' || str[i] == '-' || str[i] == '!' || str[i] == '@')
			return (str[i]);
		i++;
	}
	return (0);		
}

static int	dup_to_list(char **av, t_list **env)
{
	t_list	*new_node;
	char	*new_content;

	new_content = ft_strdup(*av);
	new_node = ft_lstnew(new_content);
	if (!new_content || !new_node)
	{
		free(new_content);
		free(new_node);
		return (perror("minishell: Malloc failure"), 1);
	}
	ft_lstadd_back(env, new_node);
	return (0);
}

int	ft_export(int ac, char **av, t_list **env)
{
	if (ac == 0)
	{
		ft_env(*env);
		return (0);
	}
	av++;
	while (*av)
	{
		if (ft_has_special_char(*av))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putchar_fd(ft_has_special_char(*av), 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else if (dup_to_list(av, env))
			return (1);
		av++;
	}
	return (0);
}

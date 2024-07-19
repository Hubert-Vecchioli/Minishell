/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:50:03 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 17:28:41 by hvecchio         ###   ########.fr       */
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
static int	ft_strchr_count(const char *str, int to_find)
{
	int	i;

	i = 0;
	while (str[i] != (char)to_find)
	{
		if (!str[i])
			return (0);
		i++;
	}
	return (i);
}

int	ft_export(int ac, char **av, t_list **env)
{
	char *tmp;
	
	if (ac == 0)
	{
		ft_env(*env);
		return (0);
	}
	av++;
	while (*av)
	{
		if (ft_strchr_count(*av, 61))
		{
			// si il y a un =, on cherche ce =
			tmp = ft_substr(*av, 0, ft_strchr_count(*av, 61) - 1);
			// MALLOC PROTECT is missing
			ft_is_var_in_env(tmp, env);
			free(tmp);
			ft_putstr_fd("ejfhejfjenfe",1);
		}
		else
		{
			ft_is_var_in_env(tmp, env);// pb de =
		}
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
	ft_putstr_fd("GDGDGFYEGFHEFE",1);
	return (0);
}

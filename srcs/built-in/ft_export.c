/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:50:03 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/30 01:10:40 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	ft_has_special_char(char *str, int n)
{
	int	i;

	i = 0;
	if (str[0] == '*' || str[0] == '$' || str[0] == '?' || str[0] == '='
		|| str[0] == '#' || str[0] == '-' || str[0] == '!' || str[0] == '@'
		|| ft_iswhitespace(str[0]) || str[0] == 123 || str[0] == 125
		|| str[0] == 42 || str[0] == '.'
		|| str[0] == '%' || str[0] == '+' || ft_isdigit(str[0]))
		return (str[0]);
	while (str[i] && i < n)
	{
		if (str[i] == '*' || str[i] == '$' || str[i] == '?' || str[i] == '+'
			|| str[i] == '%' || str[i] == '.' || str[i] == ' '
			|| str[i] == 123 || str[i] == 125 || str[i] == 42
			|| str[i] == '#' || str[i] == '-' || str[i] == '!' || str[i] == '@')
			return (str[i]);
		i++;
	}
	return (0);
}

static int	ft_dup_to_list(char **av, t_list ***env)
{
	t_list	*new_node;
	char	*new_content;

	new_content = ft_strdup(*av);
	new_node = ft_lstnew(ft_strtrim(new_content, WHITESPACES));
	if (!new_content || !new_node)
	{
		free(new_content);
		free(new_node);
		return (perror("minishell: Malloc failure"), 1);
	}
	free(new_content);
	ft_lstadd_back(*env, new_node);
	return (0);
}

int	ft_strchr_count(const char *str, char to_find)
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

static int	ft_error_check(char *av)
{
	if (ft_has_special_char(av, ft_strchr_count(av, '=')))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(av, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	else if (ft_strchr_count(av, '=') == 0
		&& ft_has_special_char(av, ft_strlen(av)))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putchar_fd(ft_has_special_char(av,
				ft_strlen(av)), STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	else if (!av[0])
		ft_putendl_fd("minishell: export: `': not a valid identifier", 2);
	return (0);
}

int	ft_export(char **av, t_list **env)
{
	char	*tmp;

	if (!*(++av))
		return (ft_print_export(*env), 0);
	while (*av)
	{
		if (ft_error_check(*av))
			return (1);
		if (ft_strchr_count(*av, '='))
		{
			tmp = ft_substr(*av, 0, ft_strchr_count(*av, '='));
			ft_is_var_in_env(tmp, env);
			free(tmp);
			if (ft_dup_to_list(av, &env))
				return (1);
		}
		else
		{
			if (!ft_is_env_var(*av, *env))
				if (ft_dup_to_list(av, &env))
					return (1);
		}
		av++;
	}
	return (0);
}

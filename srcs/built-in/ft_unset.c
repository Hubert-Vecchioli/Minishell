/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:05:21 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/28 01:57:01 by hvecchio         ###   ########.fr       */
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
		|| str[0] == 42 || str[0] == '.' || str[0] == '='
		|| str[0] == '%' || str[0] == '+' || ft_isdigit(str[0]))
		return (str[0]);
	while (str[i] && i < n)
	{
		if (str[i] == '*' || str[i] == '$' || str[i] == '?' || str[i] == '+'
			|| str[i] == '%' || str[i] == '.' || str[i] == ' ' || str[i] == '='
			|| str[i] == 123 || str[i] == 125 || str[i] == 42 || str[i] == '^'
			|| str[i] == '#' || str[i] == '-' || str[i] == '!' || str[i] == '@')
			return (str[i]);
		i++;
	}
	return (0);
}

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
	if (str1[i] == str2[i] && str2[i + 1] == '=')
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

int	ft_error_check(char *av)
{
	if (ft_has_special_char(av, strlen(av)))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(av, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	else if (!av[0])
	{
		ft_putendl_fd("minishell: unset: `': not a valid identifier", 2);
		return (1);
	}
	return (0);
}

int	ft_unset(int ac, char **av, t_list **env)
{
	int	status;

	(void) ac;
	status = 0;
	av++;
	while (*av)
	{
		if (ft_error_check(*av))
			status = 1;
		ft_is_var_in_env(*av, env);
		av++;
	}
	return (status);
}

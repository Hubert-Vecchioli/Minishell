/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:40:23 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/30 01:28:34 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putstr_n_from_m_fd(char *s, int fd, int n, int m)
{
	if (!s || fd < 0)
		return ;
	write(fd, s + m, n);
}

static int	ft_sort_lst(t_list **env)
{
	t_list	*current;
	t_list	*tmp;
	char	*content;

	current = *env;
	while (current)
	{
		tmp = current->next;
		while (tmp)
		{
			if (ft_strcmp(current->content, tmp->content) > 0)
			{
				content = current->content;
				current->content = tmp->content;
				tmp->content = content;
				current = *env;
				break ;
			}
			tmp = tmp->next;
		}
		current = current->next;
	}
	return (1);
}

static int	ft_duplicate_lst(t_list **env, t_list **new_env)
{
	t_list	*current;
	t_list	*new;
	char	*contt;

	current = *env;
	while (current)
	{
		contt = ft_strdup(current->content);
		if (!contt)
			return (ft_clean_env(new_env), 0);
		new = ft_lstnew(contt);
		if (!new)
			return (ft_clean_env(new_env), 0);
		ft_lstadd_back(new_env, new);
		current = current->next;
	}
	ft_sort_lst(new_env);
	return (1);
}

void	ft_print_export(t_list *env)
{
	t_list	*tmp;
	t_list	*save;
	int		n;

	tmp = NULL;
	if (!ft_duplicate_lst(&env, &tmp))
		return ;
	save = tmp;
	while (tmp)
	{
		n = ft_strchr_count(tmp->content, '=');
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (!n)
			ft_putstr_n_from_m_fd(tmp->content, 1, ft_strlen(tmp->content) + 1, 0);
		if (n)
		{
			ft_putstr_n_from_m_fd(tmp->content, 1, n + 1, 0);
			ft_putchar_fd('\"', 1);
			ft_putstr_n_from_m_fd(tmp->content, 1, ft_strlen(tmp->content) - n
				- 1, n + 1);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	if (save)
		ft_clean_env(&save);
}

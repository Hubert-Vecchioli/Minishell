/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 10:40:23 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/25 11:32:04 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putstr_n_from_m_fd(char *s, int fd, int n, int m)
{
	if (!s || fd < 0)
		return ;
	write(fd, s + m, n);
}

static int	ft_lstswap_content(t_list *cursor, t_list *tmp)
{
	char	*content;

	content = cursor->content;
	cursor->content = tmp->content;
	tmp->content = content;
	return (1);
}

static int	ft_sort_lst(t_list **env)
{
	t_list	*current;
	t_list	*tmp;

	current = *env;
	while (current)
	{
		tmp = current->next;
		while (tmp)
		{
			if (ft_strcmp(current->content, tmp->content) > 0)
			{
				ft_lstswap_content(current, tmp);
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

	current = *env;
	while (current)
	{
		new = ft_lstnew(current->content);
		if (!new)
			return (0);
		ft_lstadd_back(new_env, new);
		current = current->next;
	}
	return (ft_sort_lst(new_env));
}

void	ft_print_export(t_list *env)
{
	t_list	*tmp;
	int		n;

	tmp = NULL;
	if (!ft_duplicate_lst(&env, &tmp))
		return ;
	while (tmp)
	{
		n = ft_strchr_count(tmp->content, '=');
		ft_putstr_fd("declare -x  ", 1);
		ft_putstr_n_from_m_fd(tmp->content, 1, n + 1, 0);
		ft_putchar_fd('\"', 1);
		ft_putstr_n_from_m_fd(tmp->content, 1, ft_strlen(tmp->content) - n
			- 1, n + 1);
		ft_putendl_fd("\"", 1);
		tmp = tmp->next;
	}
	if (tmp)
		ft_clean_env(&tmp);
}

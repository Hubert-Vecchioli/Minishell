/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:09:56 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:27:53 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_expand_tilde(t_master_shell *md, t_cmd_tbl *lst_tab)
{
	while (lst_tab != NULL)
	{
		expand_cmd_tilde(lst_tab, md);
		lst_tab = lst_tab->next;
	}
}

int	expand_cmd_tilde(t_master_shell *md, t_cmd_tbl *tab)
{
	int		i;

	i = -1;
	if (!tab->cmd)
		return (0);
	while (tab->cmd[++i])
	{
		if (tab->cmd[i] != '~' || (tab->cmd[i + 1] && (!ft_iswhitespace(tab->cmd[i + 1]) && tab->cmd[i + 1] != 47)))
			continue ;
		if (ft_is_in_quote(tab, i))
			continue ;
		ft_expand_cmd_tilde(md, tab, &i);
	}
	return (1);
}


int	ft_is_in_quote(t_cmd_tbl *tab, int i)
{
	int		in_quotes;
	char	q_type;
	int		j;

	in_quotes = 0;
	q_type = 0;
	
	while (tab->cmd[++j] && j < i)
	{
		if ((tab->cmd[j] == 34 || tab->cmd[j] == 39))
		{
			if (in_quotes && q_type == tab->cmd[j])
				in_quotes = 0;
			else if (!in_quotes)
			{
				q_type = tab->cmd[j];
				in_quotes = 1;
			}
		}
	}
	if (in_quotes)
		return (1);
	return (0);
}

int	ft_expand_cmd_tilde(t_master_shell *md, t_cmd_tbl *tab, int *i)
{
	char 	*bf_var;
	char 	*aft_var;
	char	*tmp;
	char	*home;
	int		size;

	size = ft_strlen(tab->cmd);
	bf_var = ft_substr(tab->cmd, 0, *i);
	aft_var = ft_substr(tab->cmd, *i + 1, size - (*i + 1));
	home = getenv("HOME");
	if (!bf_var || !aft_var || !home)
		return (free(home), free(bf_var), free(aft_var), ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	tmp = ft_strjoin(bf_var, home);
	if (!tmp)
		return (free(home), free(bf_var), free(aft_var), ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	*i = ft_strlen(tmp) - 1;
	free(bf_var);
	free(home);
	free(tab->cmd);
	tab->cmd = ft_strjoin(tmp, aft_var);
	if (!tab->cmd)
		return (free(tmp), free(aft_var), ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	free(tmp);
	free(aft_var);
	return (1);
}

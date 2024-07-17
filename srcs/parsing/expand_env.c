/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:10:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:27:51 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_env_var(t_master_shell *md, t_cmd_tbl *lst_tab)
{
	while (lst_tab != NULL)
	{
		expand_cmd(lst_tab, md);
		lst_tab = lst_tab->next;
	}
}

int	expand_cmd(t_master_shell *md, t_cmd_tbl *tab)
{
	int		i;

	i = -1;
	if (!tab->cmd)
		return (0);
	while (tab->cmd[++i])
	{
		if (tab->cmd[i] != '$' || !tab->cmd[i + 1])
			continue ;
		if (ft_is_in_squote(tab, i))
			continue ;
		i++;
		ft_expand(md, tab, &i);
	}
	return (1);
}

int	ft_is_in_squote(t_cmd_tbl *tab, int i)
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
	if (in_quotes && q_type == 39)
		return (1);
	return (0);
}

int	ft_expand(t_master_shell *md, t_cmd_tbl *tab, int *i)
{
	char 	*before_var;
	char 	*var_name;
	char 	*after_var;
	int		j;
	int		size;

	size = ft_strlen(tab->cmd);
	if (tab->cmd[*i] && ft_isdigit(tab->cmd[*i]))
		return (ft_remove_var(md, tab->cmd, i, 1));
	j = 0;
	while (tab->cmd[*i + j] && ft_isalnum(tab->cmd[*i + j]))
		j++;
	if (!j)
		return (0);
	var_name = ft_substr(tab->cmd, *i, j);
	if (!var_name)
		return (ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	if (!ft_lst_find_env_var(md->env_head, var_name))
		return (free(var_name), ft_remove_var(md, tab->cmd, *i, j));
	return (free(var_name), ft_add_var(md, tab->cmd, *i, j, ft_lst_find_env_var(md->env_head, var_name)));

}

int	ft_remove_var(t_master_shell *md, t_cmd_tbl *tab, int *i, int j)
{
	char 	*bf_var;
	char 	*aft_var;
	int		size;

	size = ft_strlen(tab->cmd);
	bf_var = ft_substr(tab->cmd, 0, *i - 1);
	aft_var = ft_substr(tab->cmd, *i + j, size - (*i + j));
	if (!bf_var || !aft_var)
		return (free(bf_var), free(aft_var), ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	free(tab->cmd);*i = ft_strlen(bf_var) - 1;
	tab->cmd = ft_strjoin(bf_var, aft_var);
	if (!tab->cmd)
		return (free(bf_var), free(aft_var), ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	free(bf_var);
	free(aft_var);
	return (1);
}

int	ft_expand_var(t_master_shell *md, t_cmd_tbl *tab, int *i, int j, t_env *variable)
{
	char 	*bf_var;
	char 	*aft_var;
	char	*tmp;
	int		size;

	size = ft_strlen(tab->cmd);
	bf_var = ft_substr(tab->cmd, 0, *i - 1);
	aft_var = ft_substr(tab->cmd, *i + j, size - (*i + j));
	if (!bf_var || !aft_var)
		return (free(bf_var), free(aft_var), ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	tmp = ft_strjoin(bf_var, variable->content);
	if (!tmp)
		return (free(bf_var), free(aft_var), ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	free(bf_var);
	*i = ft_strlen(tmp) - 1;
	free(tab->cmd);
	tab->cmd = ft_strjoin(tmp, aft_var);
	if (!tab->cmd)
		return (free(tmp), free(aft_var), ft_free_cmd_tab(tab), ft_free(md), ft_exit('m'), 0);
	free(tmp);
	free(aft_var);
	return (1);
}

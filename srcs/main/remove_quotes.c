/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:13:08 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 09:41:18 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_rm_quotes_tables_and_lowercase_builtin(t_master_shell *md, t_cmd_tbl *tables)
{
	char *tmp;

	while (tables != NULL)
	{
		if (tables->cmd != NULL)
		{
			tmp = ft_dup_without_top_quote(md, tables->cmd);
			free(tables->cmd);
			tables->cmd = tmp;
			ft_get_builtin_lowercase(tables);
		}
		tables = tables->next;
	}
}

char *ft_dup_without_top_quote(t_master_shell *md, char *str)
{
	char *result;
	int i;

	if (str[0] == 34 || str[0] == 39)
	{
		result = ft_substr(str, 1, ft_strlen(str) - 1);
		if (!result)
			return (ft_free_cmd_tab(str), ft_free(md)); // ?? free tab
		return (result);
	}
	return (ft_strdup(str));
}

void	ft_get_builtin_lower(t_cmd_tbl *table)
{
	char	*result;
	int	i;

	i = -1;
	result = ft_strdup(table->cmd);
	//MALLOC PROTEC TODO
	while (i < ft_strlen(result))
		result[i] = ft_tolower(result[i]);
	convert_to_lower(result, ft_strlen(result));
	if (ft_strcmp(result, "echo")
		|| ft_strcmp(result, "pwd")
		|| ft_strcmp(result, "env"))
	{
		i = 0;
		while (i < ft_strlen(table->cmd))
			table->cmd[i] = ft_tolower(table->cmd[i]);
	}
	free(result);
}

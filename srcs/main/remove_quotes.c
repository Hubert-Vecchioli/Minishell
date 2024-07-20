/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:13:08 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 06:29:25 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_remove_quotes(char *line)
{
	int		i;

	i = -1;
	if (!line)
		return (0);
	while (line[++i])
	{
		// delete actual quotes (not the ones within ones)
		// realloc the char+
		// lowercase_builtin within quotes
	}
	return (1);
}

void	ft_lowercase_builtin(t_cmd_tbl *table)
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

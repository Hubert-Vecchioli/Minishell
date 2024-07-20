/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:13:08 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 06:42:56 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_in_quote(char *line, int i)
{
	int		in_quotes;
	char	q_type;
	int		j;

	in_quotes = 0;
	q_type = 0;
	j = -1;
	
	while (line[++j] && j < i)
	{
		if ((line[j] == 34 || line[j] == 39))
		{
			if (in_quotes && q_type == line[j])
				in_quotes = 0;
			else if (!in_quotes)
			{
				q_type = line[j];
				in_quotes = 1;
			}
		}
	}
	if (in_quotes)
		return (1);
	return (0);
}

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
		|| ft_strcmp(result, "env")) // add others
	{
		i = 0;
		while (i < ft_strlen(table->cmd))
			table->cmd[i] = ft_tolower(table->cmd[i]);
	}
	free(result);
}

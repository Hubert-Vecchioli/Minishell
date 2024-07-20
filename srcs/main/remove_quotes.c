/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:13:08 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 21:38:59 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_remove_char(char *line, int i)
{
	char 	*bf_var;
	char 	*aft_var;
	
	bf_var = ft_substr(line, 0, i);
	aft_var = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	free(line);
	line = ft_strjoin(bf_var, aft_var);
	if (bf_var)
		free(bf_var);
	if (aft_var)
		free(aft_var);
	if (!line)
		return (NULL);
	return (line);
}

// void	ft_lowercase_builtin(char *line)
// {
// 	char	*result;
// 	int	i;

// 	i = -1;
// 	result = ft_strdup(table->cmd);
// 	//MALLOC PROTEC TODO
// 	while (i < ft_strlen(result))
// 		result[i] = ft_tolower(result[i]);
// 	convert_to_lower(result, ft_strlen(result));
// 	if (ft_strcmp(result, "echo")
// 		|| ft_strcmp(result, "pwd")
// 		|| ft_strcmp(result, "env")) // add others
// 	{
// 		i = 0;
// 		while (i < ft_strlen(table->cmd))
// 			table->cmd[i] = ft_tolower(table->cmd[i]);
// 	}
// 	free(result);
// }

static char	*ft_search_quotes_to_remove(char *line)
{
	int		in_quotes;
	char	q_type;
	int i;
	
	in_quotes = 0;
	q_type = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] != 34 && line[i] != 39))
		{
			i++;
			continue ;
		}
		if (in_quotes && q_type == line[i])
		{
			in_quotes = 0;
			line = ft_remove_char(line, i);// MALLOC PROTEC MISSING
			continue ;
		}
		else if (!in_quotes)
		{
			q_type = line[i];
			in_quotes = 1;
			line = ft_remove_char(line, i); // MALLOC PROTEC MISSING
			continue ;
		}
		i++;
	}
	return (line);
}

char *ft_remove_quotes(char *line)
{
	if (!line)
		return (NULL);
	line = ft_search_quotes_to_remove(line);
	//MALLOC PROTECT
	return (line);
}

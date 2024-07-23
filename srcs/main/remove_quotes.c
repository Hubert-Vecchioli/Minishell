/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:13:08 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 16:01:52 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_remove_char(char *line, int i)
{
	char	*bf_var;
	char	*aft_var;

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

static char	*ft_search_quotes_to_remove(char *line)
{
	int		in_quotes;
	char	q_type;
	int		i;

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

char	*ft_remove_quotes(char *line)
{
	if (!line)
		return (NULL);
	line = ft_search_quotes_to_remove(line);
	return (line);
}

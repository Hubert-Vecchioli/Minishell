/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:48:55 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/07/28 02:33:39 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_in_squote(char *line, int i)
{
	int		in_quotes;
	char	q_type;
	int		j;

	in_quotes = 0;
	q_type = 0;
	j = -1;
	while (line[++j] && j <= i)
	{
		if ((line[j] == '\"' || line[j] == '\''))
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
	if (in_quotes && q_type == '\'')
		return (1);
	return (0);
}

int	ft_is_in_quote(char *line, int i)
{
	int		in_quotes;
	char	q_type;
	int		j;

	in_quotes = 0;
	q_type = 0;
	j = -1;
	while (line[++j] && j <= i)
	{
		if ((line[j] == '\"' || line[j] == '\''))
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

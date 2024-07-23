/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:13:59 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/22 16:25:29 by hvecchio         ###   ########.fr       */
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


static char	*ft_expand_cmd_tilde(char *line, int i)
{
	char 	*bf_var;
	char 	*aft_var;
	char	*home;
	int		size;

	size = ft_strlen(line);
	bf_var = ft_substr(line, 0, i);
	aft_var = ft_substr(line, i + 1, size - (i + 1));
	if (!bf_var || !aft_var)
		return (free(bf_var), free(aft_var), ft_putendl_fd("minishell: Malloc failure", 2), NULL);
	//MALLOC PROTECT IS MISSING
	home = getenv("HOME");
	free(line);
	line = ft_three_strjoin(bf_var, home, aft_var);
	//MALLOC PROTECT IS MISSING
	if (!line)
		return (free(bf_var), free(aft_var), ft_putendl_fd("minishell: Malloc failure", 2), NULL);
	free(bf_var);
	free(aft_var);
	return (line);
}

char	*ft_expand_tilde(char *line)
{
	int		i;

	i = -1;
	if (!line)
		return (NULL);
	while (line[++i])
	{
		if (line[i] != '~' || (line[i + 1] && (!ft_iswhitespace(line[i + 1]) && (line[i + 1] != '/' && line[i + 1] != 37))) 
			|| (i > 0 && !ft_iswhitespace(line[i - 1])))
			continue ;
		if (ft_is_in_quote(line, i))
			continue ;
		line = ft_expand_cmd_tilde(line, i);
	}
	return (line);
}

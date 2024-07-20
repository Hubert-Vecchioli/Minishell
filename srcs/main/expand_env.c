/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:10:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 21:21:30 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_in_squote(char *line, int i)
{
	int		in_quotes;
	char	q_type;
	int		j;

	in_quotes = 0;
	q_type = 0;
	j = -1;
	while (line[++j] && j < i)
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

static char	*ft_expand_var_replace(char* line, int i, int j, char *var_content)
{
	char 	*bf_var;
	char 	*aft_var;
	int		size;

	size = ft_strlen(line);
	bf_var = ft_substr(line, 0, i - 1);
	aft_var = ft_substr(line, i + j, size - (i + j));
	if (!bf_var || !aft_var)
		return (free(bf_var), free(var_content), free(aft_var), NULL); // GOOD MALLOC PROTEC IS MISSING
	free(line);
	if (var_content)
	{
		line = ft_three_strjoin(bf_var, var_content, aft_var);
		free(var_content);
	}
	else
		line = ft_strjoin(bf_var, aft_var);
	free(bf_var);
	free(aft_var);
	if (!line)
		return (NULL); // GOOD MALLOC PROTEC IS MISSInG
	return (line);
}

static char	*ft_expand_get_var_value(char *line, int i, t_list *lst_env)
{
	char 	*var_content;
	char 	*var_name;
	int		j;

	j = 0;
	while (line[i + j] && !ft_isdigit(line[i]) && ft_isalnum(line[i + j]))
		j++;
	if (ft_isdigit(line[i]))
		j++;
	var_name = ft_substr(line, i, j);
	var_content = ft_getenv_value(var_name, lst_env);
	// MALLOC PROTEC IS MISSInG
	line = ft_expand_var_replace(line, i, j, var_content);
	// MALLOC PROTEC IS MISSInG
	return (line);
}

char	*ft_expand_var(char *line, t_list *lst_env)
{
	int		i;

	i = -1;
	if (!line)
		return (NULL);
	while (line[++i])
	{
		if (line[i] != '$' || !line[i + 1] || (line[i] == '$' && !ft_isalnum(line[i + 1])))
			continue ;
		if (ft_is_in_squote(line, i))
			continue ;
		i++;
		line = ft_expand_get_var_value(line, i, lst_env);
	}
	return (line);
}

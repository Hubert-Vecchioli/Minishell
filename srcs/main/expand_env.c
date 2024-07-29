/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:10:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/29 13:29:27 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_heredocs_before(char *line, int i)
{
	int	j;

	j = 1;
	while ((i - j) >= 0 && line[i - j] && ft_iswhitespace(line[i - j]))
		j++;
	if ((i - j - 1) >= 0 && line[i - j] == '<' && line[i - j - 1] == '<')
		return (1);
	return (0);
}

static int	ft_has_redir_before(char *line, int i)
{
	int	j;

	j = 1;
	while ((i - j) >= 0 && line[i - j] && ft_iswhitespace(line[i - j]))
		j++;
	if (line[i - j] == '>' || line[i - j] == '<')
		return (1);
	return (0);
}

static char	*ft_expand_var_replace(char *line, int *i, int j, char *var_content)
{
	char	*bf_var;
	char	*aft_var;

	bf_var = ft_substr(line, 0, *i - 1);
	aft_var = ft_substr(line, *i + j, ft_strlen(line) - (*i + j));
	if (!bf_var || !aft_var)
		return (free(bf_var), free(var_content), free(aft_var), NULL);
	free(line);
	if (var_content)
	{
		line = ft_three_strjoin(bf_var, var_content, aft_var);
		*i = ft_strlen(bf_var) + ft_strlen(var_content) - 1;
		free(var_content);
	}
	else
	{
		line = ft_strjoin(bf_var, aft_var);
		*i -= 2;
	}
	free(bf_var);
	free(aft_var);
	if (!line)
		return (NULL);
	return (line);
}

static char	*ft_expand_get_var_value(char *line, int *i, t_list *lst_env)
{
	char	*var_content;
	char	*var_name;
	int		j;

	j = 0;
	while (line[*i + j] && !ft_isdigit(line[*i]) && ft_isalnum(line[*i + j]))
		j++;
	if (ft_isdigit(line[*i]))
		j++;
	var_name = ft_substr(line, *i, j);
	var_content = ft_getenv_value(var_name, lst_env);
	line = ft_expand_var_replace(line, i, j, var_content);
	free(var_name);
	return (line);
}

char	*ft_expand_var(char *line, t_list *lst_env, int j)
{
	int		i;

	i = -1;
	if (!line)
		return (NULL);
	while (line[++i])
	{
		if ((line[i] != '$' || !line[i + 1] || (line[i] == '$'
					&& !ft_isalnum(line[i + 1]))) && (line[i] != '$'
				|| ft_is_in_quote(line, i)
				|| (line[i + 1] != '\"' && line[i + 1] != '\'')))
			continue ;
		if (ft_is_in_squote(line, i))
			continue ;
		if (ft_has_heredocs_before(line, i))
			continue ;
		if (j == 1 && ft_has_redir_before(line, i))
			continue ;
		i++;
		line = ft_expand_get_var_value(line, &i, lst_env);
	}
	return (line);
}

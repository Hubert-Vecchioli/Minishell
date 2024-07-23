/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_errors_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:01:48 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/22 16:04:04 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_redir_before_pipe(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '|' && ft_iswhitespace(line[1]) == 1)
		return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '|'", 2), 1);
	while (line[++i])
	{
		if (i >= 2 && line[i] == '|' && line[i - 1] == '>' && line[i - 2] == '>')
			return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '|'", 2), 1);
		if (i >= 2 && line[i] == '|' && line[i - 1] == '<' && line[i - 2] == '<')
			return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '|'", 2), 1);
		if (line[i] == '|' && line[i - 1] == '>')
			return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '>'", 2), 1);
		if (line[i] == '|' && line[i - 1] == '<')
			return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '<'", 2), 1);
	}
	return (0);
}

int	ft_has_easy_syntax_error(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[++i])
	{
		if ((line[i - 1] == '|' || line[i - 1] == '<' || line[i - 1] == '>' ) && ft_iswhitespace(line[i]))
		{
			j = 0;
			while (ft_iswhitespace(line[i + j]))
				j++;
			if (line[i + j] == '|')
				return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '|'", 2), 1);
			if (line[i + j] == '<' && line[i + 1 + j] != '<')
				return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '<'", 2), 1);
			if (line[i + j] == '<' && line[i + 1 + j] == '<')
				return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '<<'", 2), 1);
			if (line[i + j] == '>' && line[i + 1 + j] != '>')
				return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '>'", 2), 1);
			if (line[i + j] == '>' && line[i + 1 + j] == '>')
				return(ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected token: '>>'", 2), 1);
			i += j;
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_errors_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:01:48 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 06:21:42 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_redir_before_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[++i])
	{
		if (line[i] == '|' && line[i - 1] == '>')
			return(perror("minishell: syntax error near unexpected char: '>'\n"), 1);
		if (line[i] == '|' && line[i - 1] == '<')
			return(perror("minishell: syntax error near unexpected char: '<'\n"), 1);
	}
	return (0);
}

int	ft_has_easy_syntax_error(char *line)
{
	int	i;

	i = 0;
	while (line[++i])
	{
		if ((line[i - 1] == '|' || line[i - 1] == '<' || line[i - 1] == '>' ) && ft_iswhitespace(line[i]))
		{
			while (ft_iswhitespace(line[i]))
				i++;
			if (line[i] == '|')
				return(perror("minishell: syntax error near unexpected char: '|'\n"), 1);
			if ((line[i] == '<' && line[i + 1] != '<'))
				return(perror("minishell: syntax error near unexpected char: '<'\n"), 1);
			if (line[i] == '>' )
				return(perror("minishell: syntax error near unexpected char: '>'\n"), 1);
		}
	}
	return (0);
}
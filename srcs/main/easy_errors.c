/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 01:18:25 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/22 11:16:21 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_has_only_tilde(char *line)
{
	char	*home_path;
	char	*home_error;
	
	if (line[0] == '~' && ft_strlen(line) == 1)
	{	
		home_path = getenv("HOME");
		ft_set_status(126);
		if (!home_path)
			return (ft_putendl_fd("minishell: ~: is a directory", 2), 1);
		else
		{
			home_error = ft_three_strjoin("minishell: ",home_path,": is a directory\n");
			return (perror(home_error), free(home_error), 1);
		}
	}
	return (0);
}

static int	ft_has_easy_errors(char *line)
{
	int i;
	
	i = 0;
	while (line[i] && line[i + 1] && line[i + 2])
	{
		if ((line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>') )
			return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected char: '>>'", 2), 1);
		if ((line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<') )
			return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected char: '<<'", 2), 1);
		i++;
	}
	if (((line[0] == 34 && line[1] == 34) || (line[0] == 39
		&& line[1] == 39)) && ft_strlen(line) == 2)
		return (ft_set_status(127), ft_putendl_fd("minishell: command not found", 2), 1);
	return (0);
}


static int	ft_has_easy_pipe_errors(char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected char: '||'", 2), 1);
	if (line[0] == '&' && line[1] == '&')
		return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected char: '&&'", 2), 1);
	else if (line[0] == '|')
		return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected char: '|'", 2), 1);
	else if ((line[ft_strlen(line) - 1] == '|' || line[ft_strlen(line) - 1] == '>'
		|| line[ft_strlen(line) - 1] == '<') || (line[0] == '!' && ft_strlen(line) == 1))
		return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected char: 'newline'", 2), 1);
	return (0);
}

static int	ft_has_easy_quotes_errors(char *line)
{
	char	q_type;
	int		i;
	int		in_quotes;

	i = -1;
	q_type = 0;
	in_quotes = 0;
	while (line[++i])
	{
		if ((line[i] == 34 || line[i] == 39))
		{
			if (in_quotes && q_type == line[i])
				in_quotes = 0;
			else if (!in_quotes)
			{
				q_type = line[i];
				in_quotes = 1;
			}
		}
	}
	if (in_quotes != 0 && q_type == 34)
		return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected char: \"", 2), 1);
	if (in_quotes != 0 && q_type == 39)
		return (ft_set_status(258), ft_putendl_fd("minishell: syntax error near unexpected char: \'", 2), 1);
	return (0);
}

int	ft_easy_error_reviews(char *line)
{
	if (!ft_strlen(line))
		return (0);
	if (ft_has_easy_errors(line))
		return (0);	
	if (ft_has_only_tilde(line))
		return (0);
	if (ft_has_easy_quotes_errors(line))	
		return (0);
	if (ft_has_easy_pipe_errors(line))
		return (0);
	if (ft_has_redir_before_pipe(line))	
		return (0);
	if (ft_has_easy_syntax_error(line))
		return (0);
	return (1);
}

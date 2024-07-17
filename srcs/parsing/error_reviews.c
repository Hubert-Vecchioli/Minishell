/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_reviews.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 07:50:15 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 10:13:00 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_easy_error_reviews(t_master_shell *master_data)
{
	master_data->trimmed_cmd = ft_strtrim(master_data->cmd, WHITESPACES);
	if (!ft_strlen(master_data->trimmed_cmd))
		return (0);
	// if (ft_has_out_of_topic_char(master_data->trimmed_cmd))
	// 	return (0);
	if (ft_has_easy_errors(master_data))
		return (0);
	if (ft_has_easy_quotes_errors(master_data))	
		return (0);
	if (ft_has_easy_pipe_errors(master_data))
		return (0);
	if (ft_has_redir_before_pipe(master_data))	
		return (0);
	if (ft_has_easy_syntax_error(master_data->trimmed_cmd))
		return (0);
	return (1);
}
// int	ft_has_out_of_topic_char(t_master_shell *md)
// {
// 	int	i;
	
// 	i = 0;
// 	while (md->trimmed_cmd[i])
// 	{
// 		if (md->trimmed_cmd[i] == 92 || md->trimmed_cmd[i] == 59)
// 			return (printf("Error, special character found\n"), 1);
// 	}
// 	return (0);
// }

int	ft_has_easy_errors(t_master_shell *md)
{
	if (md->trimmed_cmd[0] == '~' && ft_strlen(md->trimmed_cmd) == 1)
	{
		md->exit_code = 126;
		if (!ft_lst_find_env_var(md->env_head, "HOME"))
			return (printf("minishell: ~: is a directory\n"), 1);
		else
			return (printf("minishell: %s: is a directory\n", ft_lst_find_env_var(md->env_head, "HOME")->content), 1);
	}
	if ((md->trimmed_cmd[0] == '>' && md->trimmed_cmd[1] == '>'
			&& md->trimmed_cmd[2] == '>') || (md->trimmed_cmd[0] == '<'
			&& md->trimmed_cmd[1] == '<' && md->trimmed_cmd[2] == '<'))
	{
		md->exit_code = 2;
		return (printf("minishell: syntax error near unexpected char: '%c'\n", md->trimmed_cmd[0]), 1);
	}
	if (((md->trimmed_cmd[0] == 34 && md->trimmed_cmd[1] == 34)
		|| (md->trimmed_cmd[0] == 39 && md->trimmed_cmd[1] == 39))
		&& ft_strlen(md->trimmed_cmd) == 2)
	{
		printf("minishell: command not found\n");
		md->cmd_has_been_executed = 0;
		md->exit_code = 127;
		return (1);
	}
	return (0);
}

int	ft_has_easy_pipe_errors(t_master_shell *md)
{
	if (md->trimmed_cmd[0] == '|')
	{
		md->exit_code = 2;
		printf("minishell: syntax error near unexpected char: '%c'\n", md->trimmed_cmd[0]);
		return (1);

	}
	else if (md->trimmed_cmd[ft_strlen(md->trimmed_cmd) - 1] == '|' || md->trimmed_cmd[ft_strlen(md->trimmed_cmd) - 1] == '>' || md->trimmed_cmd[ft_strlen(md->trimmed_cmd) - 1] == '<')
	{
		md->exit_code = 2;
		printf("minishell: syntax error near unexpected char: 'newline' \n");
		return (1);
	}
	return (0);
}

int	ft_has_easy_quotes_errors(t_master_shell *master_data)
{
	char	q_type;
	int		i;
	int		in_quotes;

	i = -1;
	q_type = 0;
	in_quotes = 0;
	while (master_data->trimmed_cmd[++i])
	{
		if ((master_data->trimmed_cmd[i] == 34 || master_data->trimmed_cmd[i] == 39))
		{
			if (in_quotes && q_type == master_data->trimmed_cmd[i])
				in_quotes = 0;
			else if (!in_quotes)
			{
				q_type = master_data->trimmed_cmd[i];
				in_quotes = 1;
			}
		}
	}
	if (in_quotes != 0)
		return (master_data->cmd_has_been_executed = 0, master_data->exit_code = 2, printf("minishell: syntax error near unexpected char: '%c'\n", q_type), 1);
	return (0);
}


int	ft_has_redir_before_pipe(t_master_shell *master_data)
{
	int	i;

	i = 0;
	while (master_data->trimmed_cmd[++i] != '\0')
	{
		if (master_data->trimmed_cmd[i] == '|' && (master_data->trimmed_cmd[i - 1] == '>' || master_data->trimmed_cmd[i - 1] == '<') && ft_count_repetitive_char(master_data, i - 1, 92) % 2 == 0)
		{
				printf("minishell: syntax error near unexpected char: '%c'\n", master_data->trimmed_cmd[0]);
				return (1);
		}
	}
	master_data->exit_code = 2;
	master_data->cmd_has_been_executed = 0;
	return (0);
}


int	ft_count_repetitive_char(t_master_shell *master_data, int j, char c)
{
	int	i;
	int	count;

	i = j - 1;
	count = 0;
	if (j <= 0)
		return (count);
	while (i != -1)
	{
		if (master_data->trimmed_cmd[i] == c)
			count++;
		else if (master_data->trimmed_cmd[i] != c)
			return (count);
		i--;
	}
	return (count);
}

int	ft_has_easy_syntax_error(t_master_shell *master_data)
{
	int	i;

	i = 0;
	while (master_data->trimmed_cmd[i])
	{
		if ((master_data->trimmed_cmd[i - 1] == '|' || master_data->trimmed_cmd[i - 1] == '<' || master_data->trimmed_cmd[i - 1] == '>' ) && ft_iswhitespace(master_data->trimmed_cmd[i]))
		{
			while (ft_iswhitespace(master_data->trimmed_cmd[i]))
				i++;
			if ((master_data->trimmed_cmd[i] == '|' || (master_data->trimmed_cmd[i] == '<' && master_data->trimmed_cmd[i + 1] != '<') || master_data->trimmed_cmd[i] == '>' ))
			{
				master_data->exit_code = 2;
				master_data->cmd_has_been_executed = 0;
				printf("minishell: syntax error near unexpected char: '%c'\n", master_data->trimmed_cmd[i]);
				return (1);
			}
		}
	}
	return (0);
}

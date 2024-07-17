/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:30:27 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:27:55 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_generate_cmds(t_master_shell *md)
{
	md->cmd_tbls = ft_generate_cmd_tbl(md, ft_segment(md, 0, -1, -1), md);
	return (table_check(md->cmd_tbls));
}
char	**ft_segment(t_master_shell *master_data, int start, int i, int j)
{
	char	**tokens;
	char	*tmp;
	int 	quote;

	tokens = malloc(sizeof(char *) * (ft_count_pipe_segments(master_data->trimmed_cmd) + 2));
	if (tokens == NULL)
		return (ft_free(master_data), ft_exit('m'), 0); // TO REVIEW HOW TO EXIT
	while (master_data->trimmed_cmd[++i])
	{
		if (master_data->trimmed_cmd[i] == 34 || master_data->trimmed_cmd[i] == 39)
		{
			quote = master_data->trimmed_cmd[i++];
			while (master_data->trimmed_cmd[i] && master_data->trimmed_cmd[i] != quote
				&& ft_count_repetitive_char(master_data, i - 1, 92) % 2 == 0)
				i++;
		}
		if (master_data->trimmed_cmd[i] && master_data->trimmed_cmd[i] == '|'
			&& ft_count_repetitive_char(master_data, i - 1, 92) % 2 == 0)
		{
			tmp = ft_substr(master_data->trimmed_cmd, start, i - start);
			tokens[++j] = ft_strtrim(tmp, WHITESPACES);
			free(tmp);
			start = i + 1;
		}
	}
	//tmp = ft_strdup2(master_data->trimmed_cmd, start, end);
	//tokens[++j] = ft_strtrim(tmp, WHITESPACES);
	//free(tmp)
	return (tokens[j] = 0, tokens);
}

int	ft_count_pipe_segments(t_master_shell *master_data)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	while (master_data->trimmed_cmd[i])
	{
		if (master_data->trimmed_cmd[i] == 34 || master_data->trimmed_cmd[i] == 39)
		{
			quote = master_data->trimmed_cmd[i++];
			while (master_data->trimmed_cmd[i] && master_data->trimmed_cmd[i] != quote
				&& ft_count_repetitive_char(master_data, i - 1, 92) % 2 == 0)
				i++;
		}
		if (master_data->trimmed_cmd[i] && master_data->trimmed_cmd[i] == '|'
			&& ft_count_repetitive_char(master_data, i - 1, 92) % 2 == 0)
			count++;
		i++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:28:49 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 18:06:35 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_master_shell *md)
{
	if (ft_handle_tab_wth_wrong_redir(md) == 1)
	{
		ft_find_3redirs(md->trimmed_cmd);
		md->exit_code = 258;
		free_cmd_tbls(md->cmd_tbls);
		return ;
	}
	ft_handle_heredocs(md->cmd_tbls, md);
	if (g_sigint == 0 && md->cmd_tbls != NULL
		&& md->cmd_tbls->next == NULL && table_size(md->cmd_tbls) == 1)
		exec_without_pipes(md->cmd_tbls, md);
	else if (g_sigint == 0
		&& md->cmd_tbls != NULL && md->cmd_tbls->next != NULL)
	{
		md->exec_on_pipe = 1;
		exec_pipes(md->cmd_tbls, md);
	}
	free_cmd_tbls(md->cmd_tbls);
	md->cmd_tbls = NULL;
}

int	ft_handle_tab_wth_wrong_redir(t_master_shell *md)
{
	int		has_wrong_redir;
	t_cmd_tbl	*curr;

	curr = md->cmd_tbls;
	has_wrong_redir = ft_has_heredoc_with_2_redir(curr->redirs);
	while (curr && !has_wrong_redir)
	{
		curr = curr->next;
		if (curr)
			has_wrong_redir = ft_has_heredoc_with_2_redir(curr->redirs);		
	}
	if (has_wrong_redir && curr)
	{
		ft_run_heredocs_until_wrong(md->cmd_tbls, curr, md);
		return (1);
	}
	return (0);
}



int	ft_find_3redirs(char *str)
{
	int	i;

	i = 0;
	while (ft_strlen(str) > 2 && i != ft_strlen(str) - 2)
	{
		if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'
			|| str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
			return (printf("minishell: syntax error near unexpected char: '%c'\n", str[i]), 1);
		i++;
	}
	return (0);
}

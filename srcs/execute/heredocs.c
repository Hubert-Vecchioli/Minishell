/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:34:07 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 18:06:38 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_trim_quotes(char *str, t_master_shell *shell)
{
	int		i;
	char	*result;

	i = 0;
	shell->expand_heredoc = 1;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			shell->expand_heredoc = 0;
		i++;
	}
	result = ft_strtrim(str, QUOTES_TYPES);
	// MALLOC PROTECT TO ADD
	return (result);
}


void	ft_run_heredocs_until_wrong(t_cmd_tbl *start, t_cmd_tbl *last, t_master_shell *md)
{
	t_token	*token;
	char	*tmp;

	while (start != last->next)
	{
		token = start->redirs;
		while (token != NULL)
		{
			if (ft_is_redirection_tok(token) && ft_is_redirection_tok(token->next))
				return ;
			if (token->type == HEREDOC)
			{
				tmp = ft_trim_quotes(token->next->content, md);
				free(token->next->content);
				token->next->content = tmp;
				start->heredoc_name = ft_run_heredoc(start, token->next->content, md);
			}
			token = token->next;
		}
		start = start->next;
	}
}

void	ft_run_all_heredocs(t_cmd_tbl *start, t_master_shell *shell)
{
	t_token	*token;
	char	*tmp;

	token = start->redirs;
	while (token != NULL)
	{
		if (token->type == HEREDOC)
		{
			tmp = ft_trim_quotes(token->next->content, shell);
			free(token->next->content);
			token->next->content = tmp;
			start->heredoc_name = ft_run_heredoc(start, token->next->content, shell);
		}
		token = token->next;
	}
}

char	*ft_run_heredoc(t_cmd_tbl *cmd_tbl, char *delimiter, t_master_shell *shell)
{
	int		fd;
	char	*input;

	cmd_tbl->heredoc_name = ft_unlink_heredoc(cmd_tbl);
	fd = open(cmd_tbl->heredoc_name, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (fd == -1)
		p_err("minishell: %s\n", strerror(errno)); // TO CORRECT
	while (1)
	{
		write(0, "> ", 2);
		input = get_next_line(STDIN_FILENO);
		if (g_sigint == 1 || input == NULL
			|| (ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0
				&& ((ft_strlen(input) - 1) == ft_strlen(delimiter))))
		{
			free(input);
			break ;
		}
		if (shell->expand_heredoc == 1)
			expander(&input, shell); // TO DO!!!!!!!!!!
		ft_putstr_fd(input, fd);
		free(input);
	}
	shell->should_expand = 0;
	return (close(fd), cmd_tbl->heredoc_name);
}

char	*ft_unlink_heredoc(t_cmd_tbl *table)
{
	char	*tmp;
	char	*tmp1;
	char	*i;

	if (table->heredoc_name != NULL)
	{
		unlink(table->heredoc_name);
		return (table->heredoc_name);
	}
	i = ft_itoa(table->index);
	tmp = ft_strjoin("/tmp/heredoc", i);
	// MALLOC PROTECT TO ADD
	free(i);
	tmp1 = ft_strjoin(tmp, ".XXXXXX");
	// MALLOC PROTECT TO ADD
	free(tmp);
	unlink(tmp1);
	return (tmp1);
}


int	ft_has_heredoc_with_2_redir(t_token *token)
{
	while (token)
	{
		if (ft_is_redirection_tok(token)
		&& token->next && !ft_is_redirection_tok(token->next))
			return (1);
		token = token->next->next;
	}
	return (0);
}
void	ft_handle_heredocs(t_cmd_tbl *cmd_tbl, t_master_shell *shell)
{
	while (cmd_tbl)
	{
		if (ft_tab_has_heredoc(cmd_tbl))
			ft_run_all_heredocs(cmd_tbl, shell);
		cmd_tbl = cmd_tbl->next;
	}
}

int	ft_tab_has_heredoc(t_cmd_tbl *cmd_tbl)
{
	t_token	*token;

	if (!cmd_tbl)
		return (0);
	token = cmd_tbl->redirs;
	while (token)
	{
		if (token->type == HEREDOC)
			return (1);
		token = token->next;
	}
	return (0);
}


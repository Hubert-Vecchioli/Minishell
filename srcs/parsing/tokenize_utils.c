/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:49:16 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:27:57 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_tbl	*ft_init_cmd_tbl(t_master_shell *md, t_cmd_tbl *cmd_tbls, t_token *tokens)
{
	t_cmd_tbl	*new;
	t_token		*curr;

	if (tokens == NULL)
		return (0);
	new = malloc(sizeof(t_cmd_tbl));
	if (new == NULL)
		return (ft_free(md), ft_exit('m'), NULL); // MISSING FREE TOKENS AND CMDS
	new->cmd = NULL;
	new->cmd_args = NULL;
	new->args = NULL;
	new->redirs = NULL;
	new->next = NULL;
	new->heredoc_name = NULL;
	new->index = -1;
	curr = tokens;
	while (curr)
	{
		ft_get_cmd(md, new, curr);
		ft_get_arg(md, new, curr);
		ft_get_redirs(md, new, curr);
	}
	cmd_tbls = ft_cmd_add_back(cmd_tbls, new);
	return (cmd_tbls);
}

int	ft_get_redirs(t_master_shell *md, t_cmd_tbl *new, t_token *token)
{
	if (token == NULL)
		return (0);
	else if ((token->type != HEREDOC && token->type != APPEND
		&& token->type != INPUT && token->type != OUTPUT)
		&& (token->prev->type != HEREDOC && token->prev->type != APPEND
		&& token->prev->type != INPUT && token->prev->type != OUTPUT))
		return (0);
	else if ((token->type == HEREDOC || token->type == APPEND
		|| token->type == INPUT || token->type == OUTPUT)
		|| (token->prev->type == HEREDOC || token->prev->type == APPEND
		|| token->prev->type == INPUT || token->prev->type == OUTPUT))
		new->redirs = ft_token_add_back(md, new->redirs, ft_duplicate_token(token));
	token = token->next;
	return (1);
}

int	ft_get_cmd(t_master_shell *md, t_cmd_tbl *new, t_token *token)
{
	if (!token)
		return (0);
	if (new->cmd || token->type != WORD)
		return (0);
	if (token->prev && (token->prev->type == HEREDOC || token->prev->type == APPEND
		|| token->prev->type == INPUT || token->prev->type == OUTPUT))
		return (0);
	new->cmd = ft_strdup(token->content);
	if (new->cmd == NULL)
		return (ft_free(md), ft_exit('m'), NULL); // MISSING FREE TOKENS AND CMDS
	token = token->next;
	return (1);
}

int	ft_get_arg(t_master_shell *md, t_cmd_tbl *new, t_token *token)
{
	if (!token)
		return (0);
	if (token->type != WORD)
		return (0);
	if (token->prev && (token->prev->type == HEREDOC || token->prev->type == APPEND
		|| token->prev->type == INPUT || token->prev->type == OUTPUT))
		return (0);
	if (new->cmd == NULL)
		return (0);
	new->args = ft_token_add_back(md, new->args, ft_duplicate_token(token));
	token = token->next;
	return (1);
}

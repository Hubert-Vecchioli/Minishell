/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:03:54 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:28:01 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_tbl *ft_generate_cmd_tbl(t_master_shell *md, char **str_arr)
{
	int i;
	t_token *token;
	t_cmd_tbl *cmd_tab;

	cmd_tab = NULL;
	i = 0;
	while (str_arr[i])
	{
		token = NULL;
		ft_tok_segmentation(md, str_arr[i++], token);
		cmd_tab = ft_init_cmd_tbl(md, cmd_tab, token);
		ft_free_tok(token);
	}
	ft_expand_env_var(md, cmd_tab);
	ft_expand_tilde(md, cmd_tab);
	//ft_expand_heredocs(cmd_tab, md);
	ft_rm_quotes_tables_and_lowercase_builtin(md, cmd_tab);
	ft_tok_args_content_listdup(md, cmd_tab);
	ft_free_split(str_arr);
	return (cmd_tab);
}


void *ft_tok_segmentation(t_master_shell *md, t_token *token, char *str)
{
	while (str[md->tok_i])
	{
		md->tok_i = md->tok_j;
		ft_generate_tok_quote(md, token, str);
		ft_generate_tok_word(md, token, str);
		ft_generate_tok_redir(md, token, str);
		ft_generate_tok_flag(md, str, token);
		while (ft_iswhitespace(str[md->tok_i]))
			md->tok_i++;
	}
	md->tok_i = 0;
	md->tok_j = 0;
}

int	ft_generate_tok_flag(t_master_shell *md, char *str, t_token *token)
{
	int	count;
	if (str[md->tok_i] != '-')
		return (0);
	md->tok_i++;
	while (str[md->tok_i] && str[md->tok_i] != ' ')
	{
		if (!ft_isalpha(str[md->tok_i]) && str[md->tok_i] != '-' && ft_isdigit(str[md->tok_i]))
			break;
		md->tok_i++;
		count++;
	}
	token = ft_token_add_back(token, ft_new_token(ft_substr(str, md->tok_j, count), WORD));
	md->tok_j = md->tok_i;
	return (1);
}

int ft_generate_tok_redir(t_master_shell *md, t_token *token, char *str)
{
	char redirection;
	int	count;

	if (!str[md->tok_i] ||  (str[md->tok_i] != '<' && str[md->tok_i] != '>'))
		return (0);
	count = 0;
	redirection = str[md->tok_i];
	while (str[md->tok_i] && str[md->tok_i] == redirection)
	{
		md->tok_i++;
		count++;
	}
	ft_token_add_back(token, ft_new_token(md, ft_substr(str, md->tok_j, count), ft_redir_type(str, md->tok_j, md->tok_i)));
	md->tok_j = md->tok_i;
	return (1);
}

int ft_generate_tok_word(t_master_shell *md, t_token *token, char *str)
{
	int size;

	size = 0;
	while (str[md->tok_i] && (str[md->tok_i] !='<' || str[md->tok_i] != '>'))
	{
		size++;
		md->tok_i++;
	}
	if (size > 0)
		ft_token_add_back(token, ft_new_token(md, ft_substr(str, md->tok_j, size), WORD));
	md->tok_j = md->tok_i;
	return (1);
}



int ft_generate_tok_quote(t_master_shell *md, t_token *token, char *str)
{
	char quote;
	int stop;
	int size;

	if (!str[md->tok_i] || (str[md->tok_i] != 34 && str[md->tok_i] != 39))
		return (0);
	quote = str[(md->tok_i)];
	(md->tok_i)++;
	stop = 0;
	size = 0;
	while (str[md->tok_i] && stop == 0)
	{
		if (str[md->tok_i] == quote && ft_count_repetitive_char(md, md->tok_i - 1, 92) % 2 == 0)
			stop = 1;
		(md->tok_i)++;
		size++;
	}
	if (size > 1)
		ft_token_add_back(token,  ft_new_token(md, ft_substr(str, md->tok_j, size + 2), WORD));
	md->tok_j = md->tok_i;
	return (1);
}



void ft_tok_args_content_listdup(t_master_shell *md, t_cmd_tbl *tables)
{
	while (tables)
	{
		tables->cmd_args = ft_tok_content_dup(md, tables->cmd, tables->args);
		tables = tables->next;
	}
}

char **ft_tok_args_content_dup(t_master_shell *md, t_token *cmd_token, char *args)
{
	int 	size;
	char 	**result;
	int 	i;

	size = ft_toklist_len(cmd_token);
	i = 0;
	if (args)
		size += 1;
	result = malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (ft_free(md), ft_exit('m'), 0); // NEED TO FREE TOK AND CMDS
	result[size] = 0;
	if (args)
		result[i++] = ft_strdup(args);
	while (cmd_token && i < size)
	{
		result[i++] = ft_strdup(cmd_token->content);
		cmd_token = cmd_token->next;
	}
	return (result);
}

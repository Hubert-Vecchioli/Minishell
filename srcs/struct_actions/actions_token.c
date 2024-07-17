/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:43:23 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:28:03 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_add_back(t_token *token, t_token *new_elem)
{
	if (token == NULL)
	{
		token = new_elem;
	}
	else
	{
		new_elem->prev = ft_token_last(token);
		ft_token_last(token)->next = new_elem;
	}
}

t_token	*ft_new_token(t_master_shell *master_data, char *str, t_type *type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token || !str)
		return (ft_free(master_data), ft_exit('m'), NULL); // TO REVIEW HOW TO EXIT
	token->content = ft_strdup(str); // a malloc?
	if (!token->content)
		return (ft_free(master_data), ft_exit('m'), NULL); // TO REVIEW HOW TO EXIT
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*ft_token_last(t_token *lst_tokens)
{
	if (lst_tokens == NULL)
		return (NULL);
	return (lst_tokens->prev);
}

t_token	*ft_duplicate_token(t_master_shell *master_data, t_token *lst_token)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (ft_free(master_data), ft_exit('m'), NULL);
	token->content = ft_strdup(lst_token->content);
	if (!token->content)
		return (ft_free(master_data), ft_exit('m'), NULL); 
	token->type = lst_token->type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	ft_free_tok(t_token *token)
{
	t_token	*next;

	next = NULL;
	if (token == NULL)
		return ;
	while (token != NULL)
	{
		next = token->next;
		free(token->content);
		free(token);
		token = next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:39:04 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 14:40:35 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirection_tok(t_token *token)
{
	if (token == NULL)
		return (0);
	if (token->type == HEREDOC
		|| token->type == APPEND
		|| token->type == INPUT
		|| token->type == OUTPUT)
		return (1);
	return (0);
}
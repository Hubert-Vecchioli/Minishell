/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:12:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 11:11:46 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_free_arg(t_arg **arg)
{
	if (!*arg)
		return;
	if ((*arg)->arg)
		free((*arg)->arg);
	if (&((*arg)->next))
		ft_free_arg(&((*arg)->next));
	if (*arg)
		free(*arg);
}

static void ft_free_redirect(t_redir **redir)
{
	if (!*redir)
		return;
	free((*redir)->file);
	ft_free_redirect(&((*redir)->next));
	free(*redir);
}

void ft_clean_ast(t_ast **ast)
{
	if (!*ast)
		return;
	if ((*ast)->type == PIPE)
	{
		ft_clean_ast((t_ast **)&((*ast)->left));
		ft_clean_ast((t_ast **)&((*ast)->right));
	}
	else
	{
		ft_free_arg((t_arg **)&((*ast)->left));
		ft_free_redirect((t_redir **)&((*ast)->right));
	}
	free(*ast);
}

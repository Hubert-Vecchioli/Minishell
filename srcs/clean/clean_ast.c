/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:12:36 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 09:23:56 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_arg(t_arg **arg)
{
	if (!*arg)
		return ;
	free((*arg)->arg);
	clean_arg(&((*arg)->next));
	free(*arg);
	*arg = NULL;
}

static void	clean_redirect(t_redir **redir)
{
	if (!*redir)
		return ;
	free((*redir)->file);
	(*redir)->file = NULL;
	clean_redirect(&((*redir)->next));
	free(*redir);
	*redir = NULL;
}

void	ft_clean_ast(t_ast **ast)
{
	if (!*ast)
		return ;
	if ((*ast)->type == PIPE)
	{
		ft_clean_ast((t_ast **)&((*ast)->left));
		ft_clean_ast((t_ast **)&((*ast)->right));
	}
	else
	{
		clean_arg((t_arg **)&((*ast)->left));
		clean_redirect((t_redir **)&((*ast)->right));
	}
	free(*ast);
	*ast = NULL;
}

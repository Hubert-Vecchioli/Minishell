/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:24:57 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/27 09:51:15 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_ast_print_arg(t_arg *arg, int level)
{
	if (arg == NULL)
		return ;
	ft_putnbr_fd(level, 1);
	ft_putstr_fd(" - ", 1);
	ft_putendl_fd(arg->arg, 1);
	ft_ast_print_arg(arg->next, level + 1);
}

static void	ft_ast_print_redirect(t_redir *redir, int level)
{
	if (redir == NULL)
		return ;
	ft_putnbr_fd(level, 1);
	ft_putstr_fd(" - type (see minishell.h): ", 1);
	ft_putnbr_fd(redir->type, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(level, 1);
	ft_putstr_fd(" - ", 1);
	ft_putendl_fd(redir->file, 1);
	ft_ast_print_redirect(redir->next, level + 1);
}

void	ft_ast_print(t_ast *ast, int level)
{
	if (ast == NULL)
		return ;
	if (ast->type == PIPE)
	{
		ft_ast_print(ast->left, level + 1);
		ft_putnbr_fd(level, 1);
		ft_putendl_fd(" - PIPE", 1);
		ft_ast_print(ast->right, level + 1);
	}
	else
	{
		ft_putnbr_fd(level, 1);
		ft_putendl_fd(" - ARG", 1);
		ft_ast_print_arg(ast->left, level + 1);
		if (ast->right)
		{
			ft_putnbr_fd(level, 1);
			ft_putendl_fd(" - REDIRECT", 1);
		}
		ft_ast_print_redirect(ast->right, level + 1);
	}
}

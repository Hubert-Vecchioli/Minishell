/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:10:10 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 12:11:42 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_arg(t_arg *arg, int level)
{
	if (!arg)
		return ;
	printf("%*s%s\n", level, "", arg->arg);
	ft_print_arg(arg->next, level + 1);
}

static void	print_redirect(t_redir *redir, int level)
{
	if (!redir)
		return ;
	printf("%*s%d\n", level, "", redir->type);
	printf("%*s%s\n", level, "", redir->file);
	print_redirect(redir->next, level + 1);
}

void	print_ast(t_ast *ast, int level)
{
	if (!ast)
		return ;
	if (ast->type == PIPE)
	{
		print_ast(ast->left, level + 1);
		printf("%*s%s\n", level, "", "PIPE");
		print_ast(ast->right, level + 1);
	}
	else
	{
		printf("%*s%s\n", level, "", "ARGUMENT");
		ft_print_arg(ast->left, level + 1);
		if (ast->right)
			printf("%*s%s\n", level, "", "REDIRECT");
		print_redirect(ast->right, level + 1);
	}
}

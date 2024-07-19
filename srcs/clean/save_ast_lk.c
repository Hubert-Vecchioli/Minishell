/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:10:04 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 00:25:21 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_saved_ast_link(int mode, t_ast **ast)
{
	static t_ast	**save_ast = NULL;

	if (mode == 1)
		save_ast = ast;
	else
		ft_clean_ast(save_ast);
}

void	ft_clean_saved_ast_link(void)
{
	ft_handle_saved_ast_link(0, NULL);
}

void	ft_save_ast_link(t_ast **ast)
{
	ft_handle_saved_ast_link(1, ast);
}

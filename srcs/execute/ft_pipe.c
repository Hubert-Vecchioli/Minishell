/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:09:56 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 00:37:06 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	intern_child(t_intern_pipe *intern_pipe)
{
	close(intern_pipe->fd[0]);
	dup2(intern_pipe->fd[1], STDOUT_FILENO);
	close(intern_pipe->fd[1]);
	exec_ast(intern_pipe->ast->left, intern_pipe->lst_env, intern_pipe->status);
	close(STDOUT_FILENO);
}

static void	intern_parent(t_intern_pipe *intern_pipe)
{
	close(intern_pipe->fd[1]);
	dup2(intern_pipe->fd[0], STDIN_FILENO);
	close(intern_pipe->fd[0]);
	exec_ast(intern_pipe->ast->right, intern_pipe->lst_env, intern_pipe->status);
	close(STDIN_FILENO);
	waitpid(intern_pipe->pid, intern_pipe->status, 0);
}

static void	exe_pipe(t_ast *ast, t_list **lst_env, int *status)
{
	int				ret_pipe;
	t_intern_pipe	intern_pipe;

	intern_pipe.ast = ast;
	intern_pipe.lst_env = lst_env;
	intern_pipe.status = status;
	ret_pipe = pipe(intern_pipe.fd);
	if (ret_pipe == 0)
	{
		intern_pipe.pid = fork();
		if (intern_pipe.pid == 0)
			intern_child(&intern_pipe);
		else
			intern_parent(&intern_pipe);
		ft_clean_saved_ast_link();
		ft_clean_env_and_history(intern_pipe.lst_env);
	}
	else
		perror("minishell");
	exit(*intern_pipe.status);
}

void	ft_pipe(t_ast *ast, t_list **lst_env, int *status)
{
	exe_pipe(ast, lst_env, status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:09:56 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 12:21:46 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_in_child(t_intern_pipe *pipe)
{
	close(pipe->fd[0]);
	dup2(pipe->fd[1], STDOUT_FILENO);
	close(pipe->fd[1]);
	ft_execute_ast(pipe->ast->left, pipe->lst_env, pipe->status);
	close(STDOUT_FILENO);
}

static void	ft_in_parent(t_intern_pipe *pipe)
{
	close(pipe->fd[1]);
	dup2(pipe->fd[0], STDIN_FILENO);
	close(pipe->fd[0]);
	ft_execute_ast(pipe->ast->right, pipe->lst_env, pipe->status);
	close(STDIN_FILENO);
	waitpid(pipe->pid, pipe->status, 0);
}

void	ft_pipe(t_ast *ast, t_list **lst_env, int *status)
{
	int				ret_pipe;
	t_intern_pipe	in_pipe;

	in_pipe.ast = ast;
	in_pipe.status = status;
	in_pipe.lst_env = lst_env;
	ret_pipe = pipe(in_pipe.fd);
	if (ret_pipe == 0)
	{
		in_pipe.pid = fork();
		if (in_pipe.pid == 0)
			ft_in_child(&in_pipe);
		else
			ft_in_parent(&in_pipe);
		ft_clean_env_and_history(in_pipe.lst_env);
		ft_clean_saved_ast_link();
	}
	else
		perror("minishell");
	exit(*in_pipe.status);
}

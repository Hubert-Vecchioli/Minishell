/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 03:20:17 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 12:05:10 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_child_fct(char **tab, t_list **lst_env, char *cpath)
{
	char	**env;
	int		ret;

	env = ft_convert_lst_to_tab(*lst_env);
	ret = execve(cpath, tab, env);
	if (ret == -1)
		perror(tab[0]);
	ft_clean_env_and_history(lst_env);
	ft_free_split(&env);
	free(cpath);
	exit(ret);
}

static char	*sub_solve_path(char **tab, t_list **lst_env)
{
	char	*cpath;
	char	*path_value;

	path_value = ft_getenv("PATH=", *lst_env);
	cpath = solve_path(path_value, tab[0]);
	free(path_value);
	if (!cpath)
		perror("minishell: solve_path");
	return (cpath);
}

static int	ft_exec_parent_fct(char **tab, t_list **lst_env)
{
	char	*cpath;
	int		ret;
	int		status;
	pid_t	pid;

	cpath = sub_solve_path(tab, lst_env);
	if (!cpath)
		return (-1);
	ret = 0;
	if (access(cpath, X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
			ft_exec_child_fct(tab, lst_env, cpath);
		else
			waitpid(pid, &status, 0);
	}
	else
		perror(tab[0]);
	free(cpath);
	ft_clean_saved_ast_link();
	return (ret);
}

int	exec_arg(t_ast *ast, t_list **lst_env)
{
	char	**tab;
	int		ret;
	int		fd_save[2];

	fd_save[0] = dup(0);
	fd_save[1] = dup(1);
	if (ft_exec_redir(ast->right) != 0)
		return (1);
	tab = arg_to_tab(ast->left);
	if (!tab)
		perror("minishell: exec_arg");
	ret = 0;
	if (tab && tab[0] && ft_is_builtin_fct(tab[0]))
		ret = ft_exec_builtin(tab, lst_env);
	else if (tab && tab[0])
		ret = ft_exec_parent_fct(tab, lst_env);
	unlink("/tmp/.heredoc");
	dup2(fd_save[0], 0);
	dup2(fd_save[1], 1);
	close(fd_save[0]);
	close(fd_save[1]);
	ft_free_split(&tab);
	return (ret);
}

void	exec_ast(t_ast *ast, t_list **lst_env, int *status)
{
	pid_t	pid;
	t_arg	*test;

	if (!ast)
		return ;
	test = ast->left;
	if (ast->type == COMMAND && test && test->arg && ft_is_builtin_fct(test->arg))
		*status = exec_arg(ast, lst_env);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (ast->type == PIPE)
				ft_pipe(ast, lst_env, status);
			else if (ast->type == COMMAND)
				*status = exec_arg(ast, lst_env);
			ft_clean_env_and_history(lst_env);
			ft_clean_saved_ast_link();
			exit(*status);
		}
		else
			waitpid(pid, status, 0);
	}
}

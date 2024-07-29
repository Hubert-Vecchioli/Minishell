/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 03:20:17 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/29 13:22:51 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_child_fct(char **tab, t_list **lst_env,
char *cpath, int save_fd[2])
{
	char		**env;
	int			ret;
	struct stat	path_stat;
	char		*error_msg;

	path_stat.st_mode = 0;
	stat(cpath, &path_stat);
	if (((path_stat.st_mode) & S_IFMT) == S_IFDIR)
	{
		error_msg = ft_three_strjoin("minishell: ", tab[0], ": is a directory");
		ft_putendl_fd(error_msg, STDERR_FILENO);
		free(error_msg);
		free(cpath);
		ft_clean_env(lst_env);
		exit(126);
	}
	env = ft_convert_lst_to_tab(*lst_env);
	ft_close_fds(save_fd);
	ret = execve(cpath, tab, env);
	if (ret == -1)
		perror(tab[0]);
	ft_clean_env(lst_env);
	ft_free_split(&env);
	free(cpath);
	exit(ret);
}

static char	*sub_solve_path(char **tab, t_list **lst_env)
{
	char	*cpath;
	char	*path_value;

	path_value = ft_getenv("PATH=", *lst_env);
	cpath = ft_find_path(path_value, tab[0]);
	free(path_value);
	if (!cpath)
		perror("minishell: error to find path");
	return (cpath);
}

static int	ft_exec_parent_fct(char **tab, t_list **lst_env, int save_fd[2])
{
	char	*cpath;
	int		status;
	pid_t	pid;

	cpath = sub_solve_path(tab, lst_env);
	if (!cpath)
		return (-1);
	status = 0;
	if (access(cpath, X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
			ft_exec_child_fct(tab, lst_env, cpath, save_fd);
		signal(SIGINT, ft_clean_prompt2);
		waitpid(pid, &status, 0);
		signal(SIGINT, ft_clean_prompt);
		if (ft_get_wip() == 0 && ft_get_status() == 130)
			return (free(cpath), 130);
		return (free(cpath), WEXITSTATUS(status));
	}
	return (free(cpath), ft_is_path_allowed(tab[0]));
}

int	ft_execute_arg(t_ast *ast, t_list **lst_env)
{
	char	**tab;
	int		ret;
	int		save_fd[2];
	int		redir_value;

	redir_value = ft_exec_redir(ast->right);
	if (redir_value == -1)
		return (1);
	else if (redir_value == 130)
		return (unlink("/tmp/.heredoc"), 130);
	save_fd[0] = dup(0);
	save_fd[1] = dup(1);
	tab = ft_split_arg(ast->left);
	if (!tab)
		perror("minishell: exec_arg");
	ret = redir_value;
	if (tab && tab[0] && ft_is_builtin_fct(tab[0]))
		ret = ft_exec_builtin(tab, lst_env);
	else if (tab && tab[0])
		ret = ft_exec_parent_fct(tab, lst_env, save_fd);
	unlink("/tmp/.heredoc");
	dup2(save_fd[0], 0);
	dup2(save_fd[1], 1);
	close(save_fd[0]);
	return (close(save_fd[1]), ft_free_split(&tab), ret);
}

int	ft_execute_ast(t_ast *ast, t_list **lst_env, int *status)
{
	pid_t	pid;
	t_arg	*test;

	if (!ast)
		return (1);
	test = ast->left;
	if (ast->type == COMMAND && test && test->arg
		&& ft_is_prio_builtin_fct(test->arg))
		return (*status = ft_execute_arg(ast, lst_env), 1);
	pid = fork();
	if (pid == 0)
	{
		if (ast->type == PIPE)
			ft_pipe(ast, lst_env, status);
		else if (ast->type == COMMAND)
			*status = ft_execute_arg(ast, lst_env);
		ft_clean_env(lst_env);
		ft_clean_saved_ast_link();
		exit(*status);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	signal(SIGINT, ft_clean_prompt);
	return (*status = WEXITSTATUS(*status), 1);
}

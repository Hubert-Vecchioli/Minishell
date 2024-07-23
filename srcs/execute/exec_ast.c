/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 03:20:17 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 16:14:26 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_child_fct(char **tab, t_list **lst_env, char *cpath)
{
	char		**env;
	int			ret;
	struct stat	path_stat;
	char		*error_msg;

	stat(cpath, &path_stat);
	if (((path_stat.st_mode) & S_IFMT) == S_IFDIR)
	{
		error_msg = ft_three_strjoin("minishell: ", tab[0], ": is a directory");
		ft_putendl_fd(error_msg, 2);
		free(error_msg);
		free(cpath);
		ft_clean_env(lst_env);
		exit(126);
	}
	env = ft_convert_lst_to_tab(*lst_env);
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

static int	ft_exec_parent_fct(char **tab, t_list **lst_env)
{
	char	*cpath;
	int		status;
	char	*error_msg;
	pid_t	pid;

	cpath = sub_solve_path(tab, lst_env);
	if (!cpath)
		return (-1);
	status = 0;
	if (access(cpath, X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
			ft_exec_child_fct(tab, lst_env, cpath);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, ft_clean_prompt);
		return (free(cpath), status);
	}
	error_msg = ft_three_strjoin("minishell: ", tab[0],
			": command not found");
	ft_putendl_fd(error_msg, 2);
	free(error_msg);
	status = 127;
	return (free(cpath), status);
}

int	ft_execute_arg(t_ast *ast, t_list **lst_env)
{
	char	**tab;
	int		ret;
	int		save_fd[2];

	save_fd[0] = dup(0);
	save_fd[1] = dup(1);
	if (ft_exec_redir(ast->right) != 0)
		return (1);
	tab = ft_split_arg(ast->left);
	if (!tab)
		perror("minishell: exec_arg");
	ret = 0;
	if (tab && tab[0] && ft_is_builtin_fct(tab[0]))
		ret = ft_exec_builtin(tab, lst_env);
	else if (tab && tab[0])
		ret = ft_exec_parent_fct(tab, lst_env);
	unlink("/tmp/.heredoc");
	dup2(save_fd[0], 0);
	dup2(save_fd[1], 1);
	close(save_fd[0]);
	close(save_fd[1]);
	ft_free_split(&tab);
	return (ret);
}

int	ft_execute_ast(t_ast *ast, t_list **lst_env, int *status)
{
	pid_t	pid;
	t_arg	*test;

	if (!ast)
		return (1);
	test = ast->left;
	if (ast->type == COMMAND && test && test->arg
		&& ft_is_builtin_fct(test->arg))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:28:30 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/29 13:15:47 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_go_oldpwd(int ac, char **av, t_list **env)
{
	char		*old_path;
	struct stat	path_stat;

	old_path = ft_getenv_value("OLDPWD", *env);
	if (old_path)
	{
		stat(old_path, &path_stat);
		if (((path_stat.st_mode) & S_IFMT) != S_IFDIR)
		{
			ft_putendl_fd("minishell: cd: OLDPWD is not a directory", 2);
			return (free(old_path), 1);
		}
		ft_putendl_fd(old_path, 2);
		free(av[1]);
		av[1] = ft_strdup(old_path);
		ft_cd(ac, av, env);
	}
	else
	{
		ft_putendl_fd("minishell: cd: OLDPWD is not set", 2);
		return (free(old_path), 1);
	}
	return (free(old_path), 1);
}

int	ft_cd(int ac, char **av, t_list **env)
{
	t_cd		cd_var;
	struct stat	path_stat;

	if (ft_tablen(av) == 2 && !ft_strcmp(av[1], "-"))
		return (ft_go_oldpwd(ac, av, env));
	cd_var = (t_cd){.env = env};
	if (ac == 2)
		cd_var.arg = ft_strdup(av[1]);
	else if (ac > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	ft_cd_check_direct(&cd_var);
	free(cd_var.new_pwd);
	if (cd_var.ret == -1)
	{
		path_stat.st_mode = 0;
		stat(av[1], &path_stat);
		if (((path_stat.st_mode) & S_IFMT) != S_IFDIR)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(av[1], 2);
			ft_putendl_fd(": No such file or directory", 2);
			cd_var.ret = 1;
		}
	}
	return (free(cd_var.arg), free(cd_var.current_path), cd_var.ret);
}

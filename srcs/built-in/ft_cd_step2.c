/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_step2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:33:30 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 05:57:24 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_dup_path(t_cd *directory)
{
	free(directory->current_path);
	directory->current_path = ft_strdup(directory->arg);
	ft_cd_set_path_to_arg(directory);
}

void	ft_cd_set_path_to_arg(t_cd *directory)
{
	char	*pwd;
	char	*three_joins;

	pwd = (char [1024]){0};
	if (directory->current_path && directory->current_path[0] != '/')
	{
		getcwd(pwd, 1024);
		if (pwd[ft_strlen(pwd) - 1] == '/')
			three_joins = ft_three_strjoin(pwd, "", directory->current_path);
		else
			three_joins = ft_three_strjoin(pwd, "/", directory->current_path);
		free(directory->current_path);
		directory->current_path = three_joins;
	}
	ft_cd_clean_path(directory);
}

void	ft_cd_clean_path(t_cd *directory)
{
	char	*resolved_path;

	resolved_path = (char [PATH_MAX]){0};
	ft_realpath(directory->current_path, resolved_path);
	free(directory->current_path);
	directory->current_path = ft_strdup(resolved_path);
	if (!directory->current_path)
		return ;
	ft_cd_check_len(directory);
}

void	ft_cd_check_len(t_cd *directory)
{
	directory->new_pwd = ft_strdup(directory->current_path);
	if (ft_strlen(directory->current_path) + 1 > PATH_MAX
		&& ft_strlen(directory->arg) + 1 < PATH_MAX)
	{
		free(directory->current_path);
	}
	ft_cd_setenv(directory);
}

void	ft_cd_setenv(t_cd *directory)
{
	char	oldpwd[1024];

	ft_setenv("OLDPWD=", getcwd(oldpwd, 1024), directory->env);
	directory->ret = chdir(directory->current_path);
	ft_setenv("PWD=", directory->new_pwd, directory->env);
	return ;
}

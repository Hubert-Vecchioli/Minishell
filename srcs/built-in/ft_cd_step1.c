/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_step1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:28:49 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 05:57:20 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// documentation can be found here https://pubs.opengroup.org/onlinepubs/9699919799/utilities/cd.html

void	ft_cd_check_direct(t_cd *directory)
{
	if (!directory->arg && !ft_have_env_var_home(*directory->env))
		return ;
	ft_cd_check_home_var(directory);
}

void	ft_cd_check_home_var(t_cd *directory)
{
	if (!directory->arg && ft_have_env_var_home(*directory->env))
		directory->arg = ft_getenv("HOME=", *directory->env);
	ft_cd_check_beg_bslsh(directory);
}

void	ft_cd_check_beg_bslsh(t_cd *directory)
{
	if (directory->arg[0] == '/')
	{
		directory->current_path = ft_strdup(directory->arg);
		ft_cd_set_path_to_arg(directory);
		return ;
	}
	ft_cd_has_dots(directory);
}

void	ft_cd_has_dots(t_cd *directory)
{

	if (!ft_strcmp(".", directory->arg) || !ft_strcmp("..", directory->arg))
	{
		ft_cd_dup_path(directory);
		return ;
	}		
	ft_cd_get_path(directory);
}

void	ft_cd_get_path(t_cd *directory)
{
	char	*path;
	char	*cd_path;
	char	*three_joins;

	cd_path = ft_getenv("CDPATH=", *directory->env);
	if (!cd_path)
		cd_path = "";
	path = ft_subcdpath(cd_path);
	while (path)
	{
		three_joins = ft_three_strjoin(path, "/", directory->arg);
		free(three_joins);
		free(directory->current_path);
		directory->current_path = ft_strdup(three_joins);
		ft_cd_set_path_to_arg(directory);
		return ;
	}
	ft_cd_dup_path(directory);
}

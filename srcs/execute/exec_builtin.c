/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 01:00:17 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 05:57:55 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char **tab, t_list **lst_env)
{
	if (!ft_strcmp(*tab, "echo"))
		return (ft_echo(ft_tablen(tab), tab));
	else if (!ft_strcmp(*tab, "cd"))
		return (ft_cd(ft_tablen(tab), tab, lst_env));
	else if (!ft_strcmp(*tab, "pwd"))
		return (ft_pwd(ft_tablen(tab), tab));
	else if (!ft_strcmp(*tab, "export"))
		return (ft_export(ft_tablen(tab), tab, lst_env));
	else if (!ft_strcmp(*tab, "unset"))
		return (ft_unset(ft_tablen(tab), tab, lst_env));
	else if (!ft_strcmp(*tab, "env"))
		return (ft_env(*lst_env));
	else if (!ft_strcmp(*tab, "exit"))
		return (ft_exit(ft_tablen(tab), tab, ft_get_status(), lst_env));
	return (0);
}

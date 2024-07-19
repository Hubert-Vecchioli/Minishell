/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:28:30 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 11:12:18 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(int ac, char **av, t_list **env)
{
	t_cd		cd_var;

	cd_var = (t_cd){.env = env};
	if (ac >= 2)
		cd_var.arg = ft_strdup(av[1]);
	ft_cd_check_direct(&cd_var);
	free(cd_var.current_path);
	free(cd_var.arg);
	free(cd_var.new_pwd);
	return (cd_var.ret);
}

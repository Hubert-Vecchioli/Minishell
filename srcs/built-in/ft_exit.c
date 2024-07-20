/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 09:50:24 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 05:57:33 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(int ac, char **av, int status, t_list **env)
{
	(void) ac;
	(void) av;
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_set_end(1);
	ft_clean_env_and_history(env);
	// ADD THE RELEVANT FREE
	exit(status);
}

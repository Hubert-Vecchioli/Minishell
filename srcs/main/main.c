/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:01:20 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:27:37 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_master_shell	master_data;
	(void) av;
	
	if (ac != 1)
		return (printf("Error: Minishell has no arg, Minishell needs no arg"), 0);
	ft_init(&master_data, env);
	ft_minishell(&master_data);
	free_at_exit(&master_data);
	exit(master_data.exit_code);
	return (0);
}
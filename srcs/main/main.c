/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:01:20 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 10:16:19 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list		*lst_env;
	t_prompt	prompt;

	(void)av;
	if (ac != 1)
		return (printf("Error: Minishell has no arg, \
Minishell needs no arg"), 0);
	if (ft_intern_init(&prompt, env, &lst_env))
		return (1);
	ft_minishell(&prompt, lst_env);
	ft_clean_env(&lst_env);
	clear_history();
	return (ft_get_status());
}

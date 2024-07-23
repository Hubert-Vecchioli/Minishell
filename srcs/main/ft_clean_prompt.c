/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:59:16 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 08:45:18 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_prompt(int sig)
{
	(void)sig;
	write(1, "\n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_set_status(130);
}

void	ft_handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", STDOUT_FILENO);
	close(STDIN_FILENO);
	ft_set_status(130);
}

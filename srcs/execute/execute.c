/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:28:49 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:43:45 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//t_cmd_tbl

void	ft_execute(t_master_shell *md)
{
	// if wrong redir, execute only the heredocs
	// execute heredocs
	// execute the cmd has no pipe (ie. one element)
	// else execute pipes
	// free and we are done
}
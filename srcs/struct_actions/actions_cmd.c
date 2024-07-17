/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:54:48 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/15 17:02:20 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_tbl	*ft_cmd_add_back(t_cmd_tbl *cmd_tbl, t_cmd_tbl *new)
{
	t_cmd_tbl	*curr;

	if (cmd_tbl == NULL)
	{
		new->index = 0;
		return (new);
	}
	curr = cmd_tbl;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	new->index = curr->index + 1;
	return (cmd_tbl);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_tocken_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:44:52 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/15 19:46:48 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_toklist_len(t_token *token)
{
	int		i;
	t_token	*tmp;

	if (!token)
		return (0);
	i = 0;
	tmp = token;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i + 1);
}

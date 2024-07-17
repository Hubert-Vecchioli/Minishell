/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:33:12 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/16 16:28:04 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_free master_data

//ft_free_cmd_tab(tab)

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split && split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}


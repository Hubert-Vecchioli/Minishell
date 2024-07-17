/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:26:19 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:29:18 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_minishell(t_master_shell *master_data)
{
	while (1)
	{
		ft_generate_prompt(master_data);
		master_data->cmd = readline(master_data->prompt_to_display);
		if (!master_data->cmd || !ft_strcmp(master_data->cmd, "exit"))
		{
			printf("exit\n");
			break ;
		}
		if (!*master_data->cmd)
			continue ;
		add_history(master_data->cmd);
		if (ft_easy_error_reviews(master_data))
		{
			if (ft_generate_cmds(master_data))
				{
					ft_execute(master_data);
				}
		}
		// update the env
		// clean and free what's need to be free
	}
}

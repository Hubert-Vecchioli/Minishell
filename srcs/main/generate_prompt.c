/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:46:32 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:27:19 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_generate_prompt(t_master_shell *master_data)
{
	char *pwd;
	
	if (!master_data->user)
	{
		pwd = getcwd(NULL, 0);
		if (!ft_strnstr_end(pwd, master_data->user, ft_strlen(pwd)))
			ft_generate_prompt_no_tilde(master_data, pwd);
		else
			ft_generate_prompt_tilde(master_data, pwd);
	}
	else
	{
		master_data->prompt_to_display = ft_strdup("unknow_user@minihell$ ");
		if (master_data->prompt_to_display == NULL)
			return (ft_free(master_data), ft_exit('m'), 0); // TO REVIEW HOW TO EXIT
		return (1);
	}
}

int	ft_generate_prompt_no_tilde(t_master_shell *master_data, char *pwd)
{
	char *temp;
	char *prompt;
	
	temp = ft_strjoin(master_data->user, "@minishell:");
	if (temp == NULL)
		return (free(pwd), ft_free(master_data), ft_exit('m'), 0); // TO REVIEW HOW TO EXIT
	prompt = ft_strjoin(temp, pwd);
	if (prompt == NULL)
		return (free(pwd), free(temp), ft_free(master_data), ft_exit('m'), 0); // TO REVIEW HOW TO EXIT
	master_data->prompt_to_display = ft_strjoin(prompt, "$ ");
	return (free(pwd), free(temp), free(prompt), 1);
}


int	ft_generate_prompt_tilde(t_master_shell *master_data, char *pwd)
{
	char *pwd_var;
	char *temp;
	char *prompt;

	temp = ft_strjoin(master_data->user, "@minishell:~");
	if (temp == NULL)
		return (free(pwd), ft_free(master_data), ft_exit('m'), 0); // TO REVIEW HOW TO EXIT
	pwd_var = ft_strnstr_end(pwd, master_data->user, ft_strlen(pwd));
	prompt = ft_strjoin(temp, pwd_var);
	if (prompt == NULL)
		return (free(pwd), free(temp), ft_free(master_data), ft_exit('m'), 0); // TO REVIEW HOW TO EXIT
	master_data->prompt_to_display = ft_strjoin(prompt, "$ ");
	return (free(pwd), free(temp), free(prompt), 1);
}

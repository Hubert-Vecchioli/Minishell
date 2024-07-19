/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:46:32 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 11:01:39 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_gen_prpt_no_tilde(t_list **lst_env, t_prompt *prompt, char *pwd)
{
	char	*temp;
	char	*prompt_char;

	temp = ft_strjoin(prompt->user, "@minishell:");
	if (!temp)
	{
		perror("minishell: malloc failure");
		free(prompt->user);
		return (free(pwd), free(prompt), ft_clean_env_and_history(lst_env), exit(1), 0);
	}
	prompt_char = ft_strjoin(temp, pwd);
	if (!prompt_char)
	{
		perror("minishell: malloc failure");
		free(prompt->user);
		free(prompt);
		return (free(pwd), free(temp), ft_clean_env_and_history(lst_env), exit(1), 0);
	}
	prompt->prompt_to_display = ft_strjoin(prompt_char, "$ ");
	return (free(pwd), free(temp), free(prompt_char), 1);
}

static int	ft_gen_prpt_tilde(t_list **lst_env, t_prompt *prompt, char *pwd)
{
	char	*pwd_var;
	char	*temp;
	char	*prompt_char;

	temp = ft_strjoin(prompt->user, "@minishell:~");
	if (!temp)
	{
		perror("minishell: malloc failure");
		free(prompt->user);
		return (free(pwd), free(prompt), ft_clean_env_and_history(lst_env), exit(1), 0);
	}
	pwd_var = ft_strnstr_end(pwd, prompt->user, ft_strlen(pwd));
	prompt_char = ft_strjoin(temp, pwd_var);
	if (!prompt_char)
	{
		perror("minishell: malloc failure");
		free(prompt->user);
		free(prompt);
		return (free(pwd), free(temp), ft_clean_env_and_history(lst_env), exit(1), 0);
	}
	prompt->prompt_to_display = ft_strjoin(prompt_char, "$ ");
	return (free(pwd), free(temp), free(prompt_char), 1);
}

char	*ft_generate_prompt(t_list *lst_env, t_prompt *prompt)
{
	if (!prompt->prompt_to_display)
		free(prompt->prompt_to_display);
	if (!prompt->path)
		free(prompt->path);
	if (prompt->user)
	{
		prompt->path = ft_getcwd();
		if (!ft_strnstr_end(prompt->path, prompt->user
			, ft_strlen(prompt->path)))
			ft_gen_prpt_no_tilde(&lst_env, prompt, prompt->path);
		else
			ft_gen_prpt_tilde(&lst_env, prompt, prompt->path);// MALLOC PROTEC IS MISSING
		return (prompt->prompt_to_display);
	}
	else
	{
		prompt->prompt_to_display = ft_strdup("unknow_user@minihell$ ");
		if (!prompt->prompt_to_display)
		{
			free(prompt->user);
			return (ft_clean_env_and_history(&lst_env), NULL);
		}
		return (prompt->prompt_to_display);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:44:13 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 14:49:13 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_clean_prompt(int sig)
{
	(void) sig;
	g_sigint = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_master_shell(t_master_shell *master_data, char **env)
{
	signal(SIGINT, ft_clean_prompt);
	signal(SIGQUIT, SIG_IGN);
	master_data->envless = 0;
	master_data->cmd_paths = ft_split(get_path(env), ':');
	master_data->env = NULL;
	master_data->exit_code = 0;
	master_data->print = 0;
	master_data->heredoc = NULL;
	master_data->cmd_tbls = NULL;
	master_data->prev_prompt = NULL;
	master_data->trimmed_cmd = NULL;
	master_data->prompt_to_display = NULL;
	master_data->cmd_has_been_executed = 1;
	master_data->tok_i = 0;
	master_data->tok_j = 0;
	master_data->std_fds[0] = dup(STDIN_FILENO);
	master_data->std_fds[1] = dup(STDOUT_FILENO);
	ft_init_env(master_data, env);
}

static void	ft_review_basic_env(t_master_shell *master_data)
{
		char	*asbolute_pwd;
	
		master_data->envless = 1;
		master_data->cmd_paths = NULL;
		if (!ft_lst_find_env_var(master_data->env_head, "USER"))
			ft_add_back(master_data, ft_new_lst(master_data, "USER", "unknow_user"));
		if (!ft_lst_find_env_var(master_data->env_head, "SHLVL"))
			ft_add_back(master_data, ft_new_lst(master_data, "SHLVL", "1"));
		if (!ft_lst_find_env_var(master_data->env_head, "PWD"))
		{
			ft_add_back(master_data, ft_new_lst(master_data, "PWD", getcwd(asbolute_pwd, 0)));	
			free(asbolute_pwd);
		}
}

void	ft_init_env(t_master_shell *master_data, char **env)
{
	char	**tmp;
	int		i;

	i = -1;
	while (env && env[++i])
	{
		tmp = ft_split(env[i], '=');
		if (!tmp)					
			{
				ft_free(master_data);
				ft_exit();
			} 
		if (!tmp[1])
			ft_add_back(master_data, ft_new_lst(master_data, tmp[0], (char*)0));
		ft_add_back(master_data, ft_new_lst(master_data, tmp[0], tmp[1]));
		ft_free_split(tmp);
		ft_review_basic_env(master_data);
		master_data->user = getenv("USER");
	}
}

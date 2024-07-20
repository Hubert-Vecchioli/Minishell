/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:26:19 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 04:38:20 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	intern_exec(char *line, t_list *lst_env)
{
	char	**tab;
	t_ast	*ast;
	int		status;

	// expand variables
	ft_expand_var(line, lst_env);
	ft_expand_tilde(line);
	// removes quotes
	tab = ft_split_charset(line, WHITESPACES);
	if (!tab)
	{
		perror("minishell: malloc failure");
		ft_free_split(&tab);
		return ;
	}
	ast = ft_init_ast(ft_tablen(tab), tab);
	ft_save_ast_link(&ast);
	ft_free_split(&tab);
	//print_ast(ast, 0); FOR DEBUG !
	ft_execute_ast(ast, &lst_env, &status);
	ft_set_status(status);
	ft_clean_ast(&ast);
}

void	ft_free_prompt(t_prompt *prompt)
{
	free(prompt->path); 
	free(prompt->prompt_to_display);
	free(prompt);
}

void	ft_minishell(t_prompt *prompt, t_list *lst_env)
{
	char	*line;

	while (1)
	{
		ft_generate_prompt(lst_env, prompt);
		line = readline(prompt->prompt_to_display); // MALLOC PROTECTION IS MISSING
		if (!line)
			break ;
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (!ft_easy_error_reviews(line))
		{
			free(line);
			continue ;
		}
		intern_exec(line, lst_env);
		free(line);
		line = NULL;
		if (ft_get_end())
			break ;
	}
	if (ft_get_end() == 0)
		ft_putendl_fd("exit", STDOUT_FILENO);
	ft_free_prompt(prompt);
}

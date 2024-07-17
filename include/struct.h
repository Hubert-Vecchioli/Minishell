/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:27:46 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:26:59 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include <termios.h>

typedef enum e_type
{
	WORD,
	HEREDOC,
	OUTPUT,
	APPEND,
	INPUT,
	UNKNOWN
}	t_type;


typedef struct s_token
{
	t_type			type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd_tbl
{
	char				*cmd;
	t_token				*args;
	int					index;
	t_token				*redirs;
	char				**cmd_args;
	char				*heredoc_name;
	struct s_cmd_tbl	*next;
}	t_cmd_tbl;

typedef struct s_env
{
	char			*var_name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_master_shell
{
	int				print;
	char			**env;
	int				envless;
	char			*cmd;
	char			*heredoc;
	t_cmd_tbl		*cmd_tbls;
	t_env			*env_head;
	int				exit_code;
	int				std_fds[2];
	char			**cmd_paths;
	char			*prev_prompt;
	int				exec_on_pipe;
	int				should_expand;
	int				should_execute;
	int				expand_heredoc;
	struct termios	mirror_termios;
	char			*trimmed_cmd;
	char			*prompt_to_display;
	int				cmd_has_been_executed;
	int				tok_i;
	int				tok_j;
	char			*user;
}	t_master_shell;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:27:46 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 11:12:03 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include "../libft/libft.h"

typedef struct s_prompt
{
	char	*user;
	char	*path;
	char	*prompt_to_display;
}	t_prompt;

typedef struct s_ast
{
	int		type;
	void	*left;
	void	*right;
}	t_ast;

typedef struct s_arg			t_arg;
struct s_arg
{
	char	*arg;
	t_arg	*next;
};

typedef struct s_redir			t_redir;
struct s_redir
{
	int		type;
	char	*file;
	t_redir	*next;
};

typedef struct s_cd
{
	char	*current_path;
	char	*arg;
	char	*new_pwd;
	t_list	**env;
	int		ret;
}	t_cd;

typedef struct s_intern_pipe
{
	t_ast	*ast;
	t_list	**lst_env;
	int		*status;
	int		fd[2];
	pid_t	pid;
}	t_intern_pipe;

#endif

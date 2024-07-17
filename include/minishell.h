/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:01:07 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 09:27:11 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "struct.h"

# define WHITESPACES " \t\n\v\r\f"
# define REDIRECTIONS "><"

void			ft_add_back(t_master_shell *master_data, t_env *new_elem);
t_env			*ft_new_lst(t_master_shell *master_data, char *var_name, char *var_value);
t_env			*ft_lst_last(t_env *env_vars);
t_env			*ft_lst_find_env_var(t_env *env_vars, char *target_var_name);

#endif
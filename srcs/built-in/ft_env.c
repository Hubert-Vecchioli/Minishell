/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:28:49 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 14:56:45 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(int ac, char **av, t_list *env)
{
	char	*error;

	(void) ac;
	if (av && av + 1 && *(av + 1) && ft_strcmp(*(av + 1), "env"))
	{
		av++;
		error = ft_three_strjoin("minishell: env: ",*av,
				": No such file or directory");
		return (ft_set_status(127), ft_putendl_fd(error, 2), free(error), 1);
	}
	while (env)
	{
		ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	return (0);
}

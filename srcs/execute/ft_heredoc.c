/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:37:05 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 14:44:48 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(int fd, char const *delimiter)
{
	char	*next_line;

	ft_putstr_fd("> ", STDOUT_FILENO);
	next_line = get_next_line(STDIN_FILENO);
	while (next_line && ft_strcmp(delimiter, next_line))
	{
		ft_putendl_fd(next_line, fd);
		free(next_line);
		ft_putstr_fd("> ", STDOUT_FILENO);
		next_line = get_next_line(STDIN_FILENO);
	}
	free(next_line);
	return (0);
}

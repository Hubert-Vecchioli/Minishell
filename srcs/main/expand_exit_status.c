/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:47:19 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/07/23 16:51:32 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expand_cmd_exit_status(char *line, int i)
{
	char	*bf_var;
	char	*aft_var;
	char	*exit_status;
	int		size;

	size = ft_strlen(line);
	bf_var = ft_substr(line, 0, i);
	aft_var = ft_substr(line, i + 2, size - (i + 2));
	if (!bf_var || !aft_var)
		return (free(bf_var), free(aft_var), perror("minishell: \
Malloc failure"), NULL);
	exit_status = ft_itoa(ft_get_status());
	if (!exit_status)
		return (free(bf_var), free(aft_var), perror("minishell: \
Malloc failure"), NULL);
	free(line);
	line = ft_three_strjoin(bf_var, exit_status, aft_var);
	if (!line)
		return (free(bf_var), free(aft_var), free(exit_status),
			perror("minishell: Malloc failure"), NULL);
	free(bf_var);
	free(aft_var);
	free(exit_status);
	return (line);
}

char	*ft_expand_exit_status(char *line)
{
	int		i;

	if (!line)
		return (NULL);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] == '?')
		{
			if (ft_is_in_squote(line, i))
				continue ;
			line = ft_expand_cmd_exit_status(line, i);
		}
	}
	return (line);
}

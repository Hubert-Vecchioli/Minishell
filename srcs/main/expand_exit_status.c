/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/22 23:47:16 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */

#include "minishell.h"

static int	ft_is_in_squote(char *line, int i)
{
	int		in_quotes;
	char	q_type;
	int		j;

	in_quotes = 0;
	q_type = 0;
	j = -1;
	while (line[++j] && j < i)
	{
		if ((line[j] == '\"' || line[j] == '\''))
		{
			if (in_quotes && q_type == line[j])
				in_quotes = 0;
			else if (!in_quotes)
			{
				q_type = line[j];
				in_quotes = 1;
			}
		}
	}
	if (in_quotes && q_type == '\'')
		return (1);
	return (0);
}

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
		return (free(bf_var), free(aft_var), perror("minishell: Malloc failure"), NULL);
	exit_status = ft_itoa(ft_get_status());
	if (!exit_status)
		return (free(bf_var), free(aft_var), perror("minishell: Malloc failure"), NULL);
	free(line);
	line = ft_three_strjoin(bf_var, exit_status, aft_var);
	if (!line)
		return (free(bf_var), free(aft_var), free(exit_status), perror("minishell: Malloc failure"), NULL);
	free(bf_var);
	free(aft_var);
	free(exit_status);
	return (line);
}

char	*ft_expand_exit_status(char *line)
{
	int		i;

	i = -1; // PROBLEM SHOULD ONLY BE APPLIED ON THE NONE FIRST TAB ELELEM
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

// int	ft_starts_by_exit_status(char * line)
// {
// 	char	*error_full_expand;
// 	char	*exit_status;
	
// 	if (line[0] == '$' && line[1] == '?')
// 	{
// 		exit_status = ft_itoa(ft_get_status());
// 		error_full_expand = ft_three_strjoin("minishell: ",exit_status,": command not found");
// 		free(exit_status);
// 		ft_putendl_fd(error_full_expand, 2);
// 		free(error_full_expand);
// 		return (1);
// 	}
// 	return (0);
// }

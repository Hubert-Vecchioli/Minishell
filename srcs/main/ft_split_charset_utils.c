/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:47:55 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/27 10:00:48 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	c_s(char *src, char *charset, int pos)
{
	int	j;

	j = 0;
	while (charset[j])
	{
		if (src[pos] == charset[j])
			return (1);
		j++;
	}
	return (0);
}

int	ft_split_count_pipe(char *src, int *pos, int *count)
{
	if (*pos > 0 && !ft_is_in_quote(src, *pos) && src[*pos] == '|')
	{
		if (*count)
			return (1);
		else
		{
			(*pos)++;
			(*count)++;
			return (1);
		}
	}
	return (0);
}

int	ft_split_count_redirect(char *src, int *pos, int *count)
{
	if (!ft_is_in_quote(src, *pos) && (src[*pos] == '>' || src[*pos] == '<'))
	{
		if (*count)
			return (1);
		else if (src[*pos + 1] && (src[*pos + 1] == '>'
				|| src[*pos + 1] == '<'))
		{
			*(pos) += 2;
			*(count) += 2;
			return (1);
		}
		else
		{
			(*pos)++;
			(*count)++;
			return (1);
		}
	}
	return (0);
}

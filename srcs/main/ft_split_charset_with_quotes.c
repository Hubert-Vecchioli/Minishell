/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset_with_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:04:35 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/23 16:52:46 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_sep(char *src, char *charset, int pos)
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

static int	ft_ct_wd_w_qte(char *src, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (src[i])
	{
		while (src[i] && check_sep(src, charset, i) && !ft_is_in_squote(src, i))
			i++;
		if (src[i])
			count++;
		while (src[i] && (!check_sep(src, charset, i)
				|| ft_is_in_quote(src, i)))
			i++;
	}
	return (count);
}

static int	ft_ct_wd_l_w_qte(char *src, char *charset, int pos)
{
	int	count;

	count = 0;
	while (src[pos] && (!check_sep(src, charset, pos)
			|| ft_is_in_quote(src, pos)))
	{
		pos++;
		count++;
	}
	return (count);
}

static char	**ft_free(char **split, int pos)
{
	while (pos >= 0)
	{
		free(split[pos]);
		pos--;
	}
	free(split);
	return (NULL);
}

char	**ft_split_charset_with_quote(char *s, char *chset)
{
	char	**split;
	int		i;
	int		j;

	split = malloc((ft_ct_wd_w_qte(s, chset) + 1) * sizeof(char *));
	if (!split || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && check_sep(s, chset, i) && !ft_is_in_squote(s, i))
			i++;
		if (ft_ct_wd_l_w_qte(s, chset, i))
		{
			split[j] = ft_substr(s, i, ft_ct_wd_l_w_qte(s, chset, i));
			split[j] = ft_remove_quotes(split[j]);
			if (!split[j])
				return (ft_free(split, j));
			j++;
		}
		i = i + ft_ct_wd_l_w_qte(s, chset, i);
	}
	split[j] = 0;
	return (split);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset_with_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:04:35 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/27 09:54:18 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_skip_charset(char *src, char *charset, int *i)
{
	while (src[*i] && c_s(src, charset, *i) && !ft_is_in_squote(src, *i))
		(*i)++;
}

static int	ft_ct_wd_w_qte(char *src, char *charset, int count, int i)
{
	int	j;

	while (src[i])
	{
		ft_skip_charset(src, charset, &i);
		if (src[i])
			count++;
		j = 0;
		while (src[i] && (!c_s(src, charset, i) || ft_is_in_quote(src, i)))
		{
			if (ft_split_count_pipe(src, &i, &j))
				break ;
			if (ft_split_count_redirect(src, &i, &j))
				break ;
			j++;
			i++;
		}
	}
	return (count);
}

static int	ft_ct_wd_l_w_qte(char *src, char *charset, int pos)
{
	int	count;

	count = 0;
	while (src[pos] && (!c_s(src, charset, pos) || ft_is_in_quote(src, pos)))
	{
		if (ft_split_count_pipe(src, &pos, &count))
			break ;
		if (ft_split_count_redirect(src, &pos, &count))
			break ;
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

char	**ft_split_charset_with_quote(char *s, char *chset, t_list **lst_env)
{
	char	**split;
	int		i;
	int		j;

	split = malloc((ft_ct_wd_w_qte(s, chset, 0, 0) + 1) * sizeof(char *));
	if (!split || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && c_s(s, chset, i) && !ft_is_in_squote(s, i))
			i++;
		if (ft_ct_wd_l_w_qte(s, chset, i))
		{
			split[j] = ft_substr(s, i, ft_ct_wd_l_w_qte(s, chset, i));
			split[j] = ft_expand_var(ft_remove_quotes(split[j]), *lst_env, 1);
			if (!split[j])
				return (ft_free(split, j));
			j++;
		}
		i = i + ft_ct_wd_l_w_qte(s, chset, i);
	}
	split[j] = 0;
	return (split);
}

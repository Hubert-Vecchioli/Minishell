/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 06:59:14 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/27 10:01:54 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_sep(const char *src, char *charset, int pos)
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

static int	ft_count_words(const char *src, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (src[i])
	{
		while (src[i] && check_sep(src, charset, i))
			i++;
		if (src[i])
			count++;
		while (src[i] && !check_sep(src, charset, i))
			i++;
	}
	return (count);
}

static int	ft_count_word_len(const char *src, char *charset, int pos)
{
	int	count;

	count = 0;
	while (src[pos] && !check_sep(src, charset, pos))
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

char	**ft_split_charset(char const *s, char *charset)
{
	char	**split;
	int		i;
	int		j;

	split = malloc((ft_count_words(s, charset) + 1) * sizeof(char *));
	if (!split || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && check_sep(s, charset, i))
			i++;
		if (ft_count_word_len(s, charset, i))
		{
			split[j] = ft_substr(s, i, ft_count_word_len(s, charset, i));
			if (!split[j])
				return (ft_free(split, j));
			j++;
		}
		i = i + ft_count_word_len(s, charset, i);
	}
	split[j] = 0;
	return (split);
}

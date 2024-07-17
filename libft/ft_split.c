/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:51:52 by hvecchio          #+#    #+#             */
/*   Updated: 2024/05/20 00:38:30 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_count_word_len(const char *s, char c, int pos)
{
	int	count;

	count = 0;
	while (s[pos] && s[pos] != c)
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

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	split = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (split == NULL || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (ft_count_word_len(s, c, i))
		{
			split[j] = ft_substr(s, i, ft_count_word_len(s, c, i));
			if (split[j] == NULL)
				return (ft_free(split, j));
			j++;
		}
		i = i + ft_count_word_len(s, c, i);
	}
	split[j] = 0;
	return (split);
}

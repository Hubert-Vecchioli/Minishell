/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 02:55:47 by hvecchio          #+#    #+#             */
/*   Updated: 2024/06/19 12:41:18 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static t_buffer	buffer[MAX_FD];
	char			*line;
	size_t			line_len;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > MAX_FD)
		return (NULL);
	line_len = 0;
	if (!buffer[fd].size)
		buffer[fd].size = 0;
	line = ft_bfrjoin(NULL, &buffer[fd], line_len);
	line_len += buffer[fd].size;
	if (line == NULL)
		return (NULL);
	buffer[fd].size = ft_max(1, buffer[fd].size);
	while (buffer[fd].size > 0 && ft_strchr_oth(line, '\n', line_len) == 0)
	{
		buffer[fd].size = read(fd, buffer[fd].content, BUFFER_SIZE);
		if (buffer[fd].size > 0)
			line = ft_bfrjoin(line, &buffer[fd], line_len);
		line_len += buffer[fd].size;
		if (line == NULL || line_len == 0 || buffer[fd].size == -1)
			return (free(line), buffer[fd].size = 0, NULL);
	}
	return (ft_clean(line, &buffer[fd], line_len, '\n'));
}

size_t	ft_max(size_t a, size_t b)
{
	if (a >= b)
		return (a);
	return (b);
}

char	*ft_bfrjoin(char *line, t_buffer *buffer, size_t line_len)
{
	char		*result;
	size_t		i;

	if (line_len + (*buffer).size == 0)
		return (free(line), ft_calloc(1, sizeof(char)));
	result = malloc((line_len + (*buffer).size) * sizeof(char));
	if (!result)
		return (free(line), NULL);
	i = 0;
	while (i < line_len)
	{
		result[i] = line[i];
		i++;
	}
	while (i < line_len + (*buffer).size)
	{
		result[i] = (*buffer).content[i - line_len];
		i++;
	}
	free(line);
	return (result);
}

int	ft_strchr_oth(char *str, char to_find, size_t line_len)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	i = 0;
	while (i < line_len)
	{
		if (str[i] == to_find)
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_clean(char *line, t_buffer *buffer, size_t line_len, char to_find)
{
	char	*result;
	size_t	result_len;
	size_t	i;

	if (ft_strchr_oth(line, to_find, line_len) == 0)
		result_len = line_len;
	else
		result_len = ft_strchr_oth(line, to_find, line_len);
	result = malloc(sizeof(char) * (result_len + 1));
	if (!result)
		return (free(line), NULL);
	i = -1;
	while (++i < result_len)
		result[i] = line[i];
	i--;
	result[result_len] = 0;
	if (ft_strchr_oth(line, to_find, line_len) != 0)
		result[result_len - 1] = 0;
	while (++i < line_len)
		(*buffer).content[i - result_len] = line[i];
	(*buffer).size = line_len - result_len;
	free(line);
	return (result);
}

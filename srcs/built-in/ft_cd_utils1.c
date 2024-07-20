/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:02:27 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/20 05:57:27 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	ft_have_env_var_home(t_list *env)
{
	while (env)
	{
		if (!ft_strncmp("HOME=", env->content, ft_strlen("HOME=")))
			return (1);
		env = env->next;
	}
	return (0);
}

char	*ft_subcdpath(char *cdpath)
{
	size_t		i;
	char		*sub_cd_path;
	static char	*sub_path = NULL;

	if (!sub_path)
		sub_path = cdpath;
	if (!sub_path[0])
	{
		sub_path = NULL;
		return (NULL);
	}
	i = 0;
	while (sub_path[i] && sub_path[i] != ':')
		i++;
	if (i == 0)
		sub_cd_path = ft_strdup(".");
	else
		sub_cd_path = ft_strndup(sub_path, i);
	if (!sub_cd_path)
		return (NULL);
	sub_path += i;
	if (sub_path[0] == ':')
		sub_path++;
	return (sub_cd_path);
}

char	*ft_three_strjoin(char *str1, char *str2, char *str3)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char)
			* (ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1));
	if (!str)
		return (NULL);
	j = 0;
	i = 0;
	while (str1[j])
		str[i++] = str1[j++];
	j = 0;
	while (str2[j])
		str[i++] = str2[j++];
	j = 0;
	while (str3[j])
		str[i++] = str3[j++];
	str[i] = 0;
	return (str);
}

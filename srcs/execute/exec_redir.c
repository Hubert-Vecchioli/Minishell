/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 04:40:17 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/25 11:30:56 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_redir_input(char *file)
{
	int	new_fd;

	new_fd = open(file, O_RDONLY);
	if (new_fd == -1)
	{
		perror(file);
		return (0);
	}
	dup2(new_fd, STDIN_FILENO);
	close(new_fd);
	return (1);
}

static int	ft_redir_heredoc(char *file)
{
	int		fd;

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY, 0666);
	if (fd == -1)
	{
		perror("/tmp/.heredoc");
		return (0);
	}
	signal(SIGINT, ft_handle_sigint_heredoc);
	ft_set_status(0);
	ft_heredoc(fd, file);
	signal(SIGINT, ft_clean_prompt);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	if (fd == -1)
	{
		perror("/tmp/.heredoc");
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (ft_get_status() == 130)
		return (2);
	return (1);
}

static int	ft_redir_output(char *file)
{
	int	new_fd;

	new_fd = open(file, O_CREAT | O_WRONLY, 0666);
	if (new_fd == -1)
	{
		perror(file);
		return (0);
	}
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (1);
}

static int	ft_redir_append(char *file)
{
	int		new_fd;

	new_fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (new_fd == -1)
	{
		perror(file);
		return (0);
	}
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (1);
}

int	ft_exec_redir(t_redir *redir)
{
	int	i;

	i = 1;
	while (redir)
	{
		if (redir->type == INPUT)
			i = ft_redir_input(redir->file);
		else if (redir->type == OUTPUT)
			i = ft_redir_output(redir->file);
		else if (redir->type == APPEND)
			i = ft_redir_append(redir->file);
		else if (redir->type == HEREDOC)
		{
			i = ft_redir_heredoc(redir->file);
			if (i == 2)
				return (130);
		}
		if (i == 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

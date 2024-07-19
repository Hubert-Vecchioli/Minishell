/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 04:40:17 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 01:23:47 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_input(char *file)
{
	int	new_fd;

	new_fd = open(file, O_RDONLY);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	dup2(new_fd, STDIN_FILENO);
	close(new_fd);
	return (0);
}

static int	redir_heredoc(char *file)
{
	int		fd;

	fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY, 0666);
	if (fd == -1)
	{
		perror("/tmp/.heredoc");
		return (-1);
	}
	signal(SIGINT, ft_handle_sigint_heredoc);
	ft_heredoc(fd, file);
	signal(SIGINT, ft_clean_prompt);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	if (fd == -1)
	{
		perror("/tmp/.heredoc");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redir_output(char *file)
{
	int	new_fd;

	new_fd = open(file, O_CREAT | O_WRONLY, 0666);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (0);
}

static int	redir_append(char *file)
{
	int		new_fd;

	new_fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (0);
}

int	ft_exec_redir(t_redir *redir)
{
	int	ret;

	ret = 0;
	while (redir)
	{
		if (redir->type == INPUT)
			ret = redir_input(redir->file);
		else if (redir->type == HEREDOC)
			ret = redir_heredoc(redir->file);
		else if (redir->type == OUTPUT)
			ret = redir_output(redir->file);
		else if (redir->type == APPEND)
			ret = redir_append(redir->file);
		if (ret != 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

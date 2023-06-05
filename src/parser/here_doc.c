/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:06:16 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/05 12:51:57 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	add_line(t_heredoc **hrdc, t_heredoc *new_hrdc)
{
	t_heredoc	*tmp;

	tmp = *hrdc;
	if (new_hrdc == NULL)
	{
		free_hrdc(hrdc);
		return (EXIT_FAILURE);
	}
	if (*hrdc == NULL)
		*hrdc = new_hrdc;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_hrdc;
	}
	return (EXIT_SUCCESS);
}

static	t_heredoc	*new_doc(char *line)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
	{
		free(line);
		return (NULL);
	}
	new->line = ft_strdup(line);
	new->next = NULL;
	return (new);
}

static	int	write_to_pipe(t_heredoc *hrdc, int fd[2])
{
	while (hrdc)
	{
		write(fd[1], (hrdc->line), ft_strlen(hrdc->line));
		write(fd[1], "\n", 1);
		hrdc = hrdc->next;
	}
	close (fd[1]);
	close (fd[0]);
	free_hrdc(&hrdc);
	return (0);
}

static	void	process_hrdc(char	*delim, int fd[2])
{
	char		*line;
	t_heredoc	*heredoc;

	heredoc = NULL;
	while (1)
	{
		heredoc_signal();
		line = readline("> ");
		if (ft_strlen(line) > 0)
		{
			if (ft_strncmp(delim, line, ft_strlen(line)) != 0)
			{
				if (add_line(&heredoc, new_doc(line)) == EXIT_FAILURE)
					exit (-1);
			}
			else
			{
				free(line);
				break ;
			}
		}
		free(line);
	}
	write_to_pipe(heredoc, fd);
	ft_clear_everything(g_info);
}

int	here_doc(char	*delim)
{
	struct termios	t;
	int				ret;
	int				fd[2];
	int				pid;

	if (pipe(fd) < 0)
		ft_error(EPIPE, "");
	switch_echoctl(&t, OFF);
	pid = fork();
	if (pid < 0)
		ft_error(EPIPE, "");
	if (pid == 0)
	{
		process_hrdc(delim, fd);
		exit(0);
	}
	else
	{
		wait(&ret);
		switch_echoctl(&t, ON);
		ret = WEXITSTATUS(ret);
		g_info.exit_value = ret;
		close(fd[1]);
		return (fd[0]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:06:16 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/05 13:44:09 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	process_hrdc(char	*delim, int fd[2])
{
	char		*line;

	while (1)
	{
		heredoc_signal();
		line = readline("> ");
		if (ft_strlen(line) > 0)
		{
			if (ft_strncmp(delim, line, ft_strlen(line)) != 0)
			{
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
			}
			else
			{
				free(line);
				break ;
			}
		}
		free(line);
	}
	close (fd[1]);
	close (fd[0]);
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

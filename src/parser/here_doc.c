/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:12:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/09 14:47:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_to_pipe(char *line, int *fd)
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
}

static	void	process_hrdc(char	*delim, int fd[2])
{
	char			*line;
	struct termios	t;

	while (1)
	{
		switch_echoctl(&t, OFF);
		heredoc_signal();
		line = readline("> ");
		if (!line)
			exit(0);
		if (ft_strlen(line) > 0)
		{
			if (ft_strncmp(delim, line, ft_strlen(line)) != 0)
				write_to_pipe(line, fd);
			else
			{
				free(line);
				break ;
			}
		}
		free(line);
	}
	close (fd[0]);
	close (fd[1]);
}

int	here_doc(char	*delim)
{
	int				ret;
	int				fd[2];
	int				pid;
	struct termios	t;

	if (pipe(fd) < 0)
		ft_error(EPIPE, "");
	global_signal(OFF);
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

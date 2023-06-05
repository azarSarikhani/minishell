/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:47:58 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/05 13:45:14 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

static void	enter_file_fds(t_command *command, int **pipes, int i)
{
	if (command->infile && pipes[i][0] != 0)
	{
		if (close(pipes[i][0]) < 0)
			ft_error(EPIPE, "");
		pipes[i][0] = command->fds[0];
	}
	if (command->outfile && pipes[i + 1][1] != 0)
	{
		if (close(pipes[i + 1][1]) < 0)
			ft_error(EPIPE, "");
		pipes[i + 1][1] = command->fds[1];
	}
	else if (pipes[i + 1][1] == 0)
		pipes[i + 1][1] = 1;
}

static void	set_pipes(int **pipes, int n_cmd)
{
	int	i;

	i = 1;
	while (i < n_cmd)
	{
		if (pipe(pipes[i]) < 0)
			ft_error(EPIPE, "");
		i++;
	}
}

static int	**create_int_matrix(size_t n_elements, size_t n_entries)
{
	int		**fds;
	size_t	i;

	fds = ft_calloc(n_elements, sizeof(int *));
	if (!fds)
		return (NULL);
	i = 0;
	while (i < n_elements)
	{
		fds[i] = ft_calloc(n_entries, sizeof(int));
		if (!fds)
		{
			ft_free_int_array(&fds, i);
			return (NULL);
		}
		i++;
	}
	return (fds);
}

int	**set_up_pipes(t_command *command, int n_cmd)
{
	int	i;
	int	**pipes;

	i = 0;
	if (!command)
		return (NULL);
	pipes = create_int_matrix(n_cmd + 1, 2);
	if (!pipes)
		return (NULL);
	set_pipes(pipes, n_cmd);
	while (i < n_cmd)
	{
		enter_file_fds(command, pipes, i);
		i++;
		command = command->next;
	}
	return (pipes);
}

void	close_fds(int **fds, int cur, int n_cmd)
{
	int	pipe;

	pipe = 0;
	while (pipe <= n_cmd)
	{
		if (pipe != cur && pipe != n_cmd && fds[pipe][0] > 0)
			close(fds[pipe][0]);
		if (pipe != cur + 1 && fds[pipe][1] > 1)
			close(fds[pipe][1]);
		pipe++;
	}
	if (cur == n_cmd)
		ft_wait();
}


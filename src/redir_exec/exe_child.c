/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:22:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/05 13:08:58 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "parser.h"
#include "minishell.h"

static int	dup_fds(int **fds, int current)
{
	if (fds[current][0] != 0)
	{
		if (dup2(fds[current][0], STDIN_FILENO) < 0)
		{
			ft_error(EBADF, "");
			return (EPIPE);
		}
	}
	if (fds[current + 1][1] != 1)
	{
		if (dup2(fds[current + 1][1], STDOUT_FILENO) < 0)
		{
			ft_error(EBADF, "");
			return (EPIPE);
		}
	}
	return (0);
}

size_t	count_commands( t_command *command)
{
	size_t	n_cmd;

	n_cmd = 0;
	while (command)
	{
		command = command->next;
		n_cmd++;
	}
	return (n_cmd);
}

t_command	*get_command(t_command *command, int cur)
{	
	while (cur--)
		command = command->next;
	return (command);
}

void	exe_child(t_command *command, int **fds, int cur, t_env *env)
{
	char		**env_arr;
	t_command	*tmp;

	close_fds(fds, cur, g_info.n_cmd);
	dup_fds(fds, cur);
	tmp = get_command(command, cur);
	if (!tmp->command || !tmp->command[0])
	{
		ft_error(NOCMMD, "");
		exit(127);
	}
	env_arr = ft_env_to_array(env);
	execve(tmp->command, tmp->params, env_arr);
	ft_error(NOCMMD, tmp->command);
	ft_clear_everything(g_info);
	exit (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:07:44 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/25 10:07:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

void	ft_wait(void)
{
	int	status;

	status = 0;
	if (g_info.exit_value == 0)
	{
		while (wait(&status) > 0)
			;
		if (status > 0 && !g_info.exit_value)
			g_info.exit_value = 130;
		else if (status < 0 && !g_info.exit_value)
			g_info.exit_value = WEXITSTATUS(status);
		while (wait(&status) > 0)
			;
	}
	return ;
}

static int	**set_up_exe(t_command *command, t_env *env)
{
	int	**pipes;

	get_exe_path(&env, command);
	if (!command)
		return (NULL);
	g_info.n_cmd = count_commands(command);
	pipes = set_up_pipes(command, g_info.n_cmd);
	if (!pipes)
		return (NULL);
	return (pipes);
}

int	redirect_exe(t_command *command, t_env *env)
{
	t_command	*tmp;	
	int			i;

	if (!command || !env)
		return (-1);
	g_info.fds = set_up_exe(command, env);
	g_info.pids = ft_calloc(g_info.n_cmd, sizeof(int));
	if (!g_info.fds)
		return (1);
	i = -1;
	tmp = command;
	while (++i < g_info.n_cmd)
	{
		if (exec_builtin(&env, tmp, g_info.fds[i + 1][1]) < 0)
		{
			g_info.pids[i] = fork();
			if (g_info.pids[i] < 0)
				ft_error(EPIPE, "");
			if (g_info.pids[i] == 0)
				exe_child(command, g_info.fds, i, env);
		}
		tmp = tmp->next;
	}
	close_fds(g_info.fds, g_info.n_cmd, g_info.n_cmd);
	return (0);
}

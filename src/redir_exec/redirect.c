/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:52:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/09 11:52:55 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

static int	*set_up_pipes(t_command *command, int n_cmd)
{
	int	i;
	int	*pipes;

	i = 0;
	pipes = malloc(n_cmd * 2);
	while (i < n_cmd)
	{
		if (pipe(pipes + i) < 0)
			ft_error(EPIPE, "");
		if (command->infile)
		{
			if (close(pipes[i]) < 0)
				ft_error(EPIPE, "");
		}
		if (command->outfile)
		{
			if (close(pipes[i + 1]) < 0)
				ft_error(EPIPE, "");
		}
		i += 2;
	}

}

static void	ft_wait(t_command *cmds, int *pids)
{
	int			status;
	int			i;

	status = 0;
	i = 0;
	while (wait(&status) > 0)
		;
	if (status > 0)
	{
		free_cmds(&cmds, &pids);
		ft_error(0, "");
	}
	return ;
}

static int	*set_up_exe(t_command *command, t_env *env, size_t *n_cmds)
{
	int	*pipes;

	*n_cmds = count_commands(command);
	pipes = set_up_pipes(command, n_cmds);
	get_exe_path(command, env);
	return (pipes);
}

//set_up_pipes is not taking the array yet. Need to work out how to let the already open files go in there.
// Also need to remember to close the files that were opened and then closed in parser.c

int	redirect_exe(t_command *command, t_env *env)
{
	size_t	n_cmds;
	pid_t	*pids;
	char	**env_arr;
	int		*fds;
	int		i;

	n_cmds = 0;
	set_up_exe(command, env, &n_cmds);
	pids = ft_calloc(n_cmds, sizeof(int));
	env_arr = ft_env_to_array(env);
	i = 0;
	while (i < n_cmds)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			ft_error(EPIPE, "");
		if (pids[i] == 0)
			do_child(command, i, env);
		i++;
	}
	close_fds(command, n_cmds);
	ft_wait(command, pids); //to do
	free_cmds(&command, &pids);
	return (0);
}

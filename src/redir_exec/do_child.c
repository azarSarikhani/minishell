/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:22:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/08 15:24:23 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "minishell.h"

void	do_child(t_command *head, int (*fds[2]), int current, char **env_arr)
{
	size_t		n_cmd;
	t_command	*tmp;

	n_cmd = count_commands(head);
	tmp = set_command(head, current);
	close_fds(head, fds, current, n_cmd);
	if (dup2(tmp->fds[0], STDIN_FILENO) < 0
		|| dup2(tmp->fds[1], STDOUT_FILENO) < 0)
		ft_error(0, "");
	close(tmp->fds[0]);
	close(tmp->fds[1]);
	if (!tmp->command)
		ft_error(NOCMMD, "");
	execve(tmp->command, tmp->params, env_arr);
	ft_error(NOCMMD, tmp->command);
}
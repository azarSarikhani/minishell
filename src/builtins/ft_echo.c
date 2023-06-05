/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/02 14:05:42 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int	skip_n(t_command *cmd, BOOL *n_flag)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->params[i] && !ft_strncmp(cmd->params[i], "-n", 2))
	{
		j = 2;
		while (cmd->params[i][j] == 'n')
			j++;
		if (!cmd->params[i][j] && i == 1)
			*n_flag = 1;
		else if (cmd->params[i][j])
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(t_env **env, t_command *cmd, int out_fd)
{
	BOOL	n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	if (!env)
		return (EXIT_FAILURE);
	i = skip_n(cmd, &n_flag);
	while (cmd->params[i])
	{
		ft_putstr_fd(cmd->params[i++], out_fd);
		if (cmd->params[i] && cmd->params[i][0])
			write(out_fd, " ", 1);
	}
	if (!n_flag)
		write(out_fd, "\n", 1);
	return (EXIT_SUCCESS);
}

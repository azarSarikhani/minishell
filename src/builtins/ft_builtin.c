/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:29:10 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/27 11:46:58 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_built_in(t_ev **env, t_command *cmd)
{
	const t_builtin	**builtins[] = {
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"pwd", &ft_pwd},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{"env", &ft_env}
	};
	int				i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd->command, builtins[i][1]) == 0)
			builtins[i][2](env, cmd);
	}
	
}
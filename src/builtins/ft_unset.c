/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/09 15:54:32 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env **env, t_command *cmd, int out_fd)
{
	t_env	*remove;
	size_t	elements;
	size_t	i;

	if (!env || !*env || out_fd < 0)
		return (EXIT_FAILURE);
	i = 0;
	elements = ft_count_elements(cmd->params);
	while (++i < elements && elements > 1)
	{
		if (valid_env(cmd->params[i]) < 0)
		{
			ft_error(ARGERR2, cmd->params[i]);
			return (1);
		}
		remove = find_env(env, cmd->params[i], 0);
		if (remove)
		{
			if (remove->value)
				ft_free(remove->value);
			remove->value = NULL;
			remove->print = 0;
		}
	}
	return (0);
}

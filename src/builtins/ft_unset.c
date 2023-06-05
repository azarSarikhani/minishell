/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/05 10:17:36 by djagusch         ###   ########.fr       */
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
	while (i < elements && elements > 1)
	{
		remove = find_env(env, cmd->params[i], 0);
		if (remove)
		{
			ft_free(remove->value);
			remove->value = ft_calloc(1, sizeof(char));
		}
		i++;
	}
	return (0);
}

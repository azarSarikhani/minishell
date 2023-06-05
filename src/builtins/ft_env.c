/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/02 14:05:52 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env **env, t_command *cmd, int out_fd)
{
	t_env	*tmp;

	tmp = *env;
	cmd = NULL;
	while (tmp)
	{
		if (tmp->value[0] && ft_strcmp(tmp->key, "?"))
			ft_printf_fd(out_fd, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

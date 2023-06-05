/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/03 08:59:48 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_env(char *arg)
{
	int	i;
	int	eq_pos;

	if (!ft_isalpha(arg[0]) || arg[0] != '_')
		return (-1);
	i = 0;
	eq_pos = 0;
	while (arg[eq_pos] && arg[eq_pos] != '=')
		eq_pos++;
	while (i < eq_pos && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	return (i);
}

static int	replace_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	if (!env || !*env
		|| !key || !*key)
		return (-1);
	tmp = find_env(env, key, 0);
	if (!tmp)
	{
		tmp = new_env(key, value);
		if (!tmp)
			return (-1);
		add_env(env, tmp);
	}
	else
	{
		free(tmp->value);
		tmp->value = value;
	}
	return (0);
}

int	ft_export(t_env **env, t_command *cmd, int out_fd)
{
	size_t	i;
	size_t	elems;
	int		eq_pos;
	char	**env_str;
	int		ret;

	if (!cmd || !cmd->params)
		return (1);
	i = 0;
	elems = ft_count_elements(cmd->params);
	if (elems == 1)
		return (print_export(env, cmd, out_fd));
	while (++i < elems)
	{
		eq_pos = invalid_env(cmd->params[i]);
		env_str = split_env(cmd->params[i]);
		if (!env_str)
			return (1);
		ret = replace_env(env, env_str[0], env_str[1]);
	}
	ft_free_array(&env_str, 2);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:07:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/03 10:12:49 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_env_to_arr(t_env *env, char *envp)
{
	ft_memmove(envp, env->key, ft_strlen(env->key) * sizeof(char));
	ft_memmove(envp + ft_strlen(env->key), "=", sizeof(char));
	ft_memmove(envp + (ft_strlen(env->key) + 1) * sizeof(char),
		env->value, ft_strlen(env->value));
}

size_t	ft_env_len(t_env *env)
{
	size_t	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

char	**ft_env_to_array(t_env *env)
{
	char	**envp;
	size_t	env_len;
	size_t	i;

	i = 0;
	env_len = ft_env_len(env);
	envp = ft_calloc(env_len + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[i] = ft_calloc(ft_strlen(env->key) + ft_strlen(env->value) + 2,
				sizeof(char));
		if (!envp[i])
		{
			ft_free_array(&envp, i);
			return (NULL);
		}
		copy_env_to_arr(env, envp[i]);
		env = env->next;
		i++;
	}
	return (envp);
}

t_env	*find_env(t_env **env, char *key, int predecessor)
{
	t_env	*tmp;

	if (!env || !*env || !key || !(*key))
		return (NULL);
	tmp = *env;
	if (!predecessor)
	{
		while (tmp && ft_strcmp(key, tmp->key) != 0)
			tmp = tmp->next;
	}
	else if (ft_strcmp(key, tmp->key) == 0)
		return (tmp);
	else
	{
		while (tmp->next && ft_strcmp(key, tmp->next->key) != 0)
			tmp = tmp->next;
	}
	return (tmp);
}

char	*find_value(t_env **env, char *key)
{
	t_env	*tmp;

	if (!env || !*env || !key || !(key[0]))
		return (NULL);
	tmp = *env;
	while (tmp && ft_strcmp(key, tmp->key) != 0)
		tmp = tmp->next;
	if (tmp)
		return (tmp->value);
	return (NULL);
}

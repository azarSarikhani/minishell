/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/21 18:36:56 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = *env;
	if (*env == NULL)
	{
		*env = new;
		(*env)->next = NULL;
	}	
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static char	**split_env(char *envp)
{
	char	**tmp;
	char	*eq;

	eq = ft_strchr(envp, '=');
	tmp = ft_calloc(3, sizeof(char *));
	if (!tmp)
		return (NULL);
	if (eq)
	{
		tmp[0] = ft_substr(envp, 0, eq - envp);
		tmp[1] = ft_strdup(eq + 1);
	}
	if (!tmp[0])
		return (NULL);
	if (tmp && ft_strcmp(tmp[0], "SHLVL") == 0)
		tmp[1] = ft_itoa(ft_atoi(tmp[1]) + 1);
	return (tmp);
}

void	init_env(char *envp[], t_env **env)
{
	char	**tmp;
	t_env	*new;

	while (*envp)
	{
		tmp = split_env(*envp);
		if (!tmp)
			break ;
		new = new_env(tmp[0], tmp[1]);
		ft_free_array(&tmp, 2);
		if (!new)
			break ;
		add_env(env, new);
		envp++;
	}
}

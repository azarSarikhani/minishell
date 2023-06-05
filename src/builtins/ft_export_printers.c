/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_printers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/03 09:51:54 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_env(t_env **env)
{
	t_env	*tmp;
	t_env	*list;
	t_env	*new;

	if (!env || !*env)
		return (NULL);
	list = NULL;
	add_env(&list, new_env((*env)->key, (*env)->value));
	if (!list)
		return (NULL);
	tmp = (*env)->next;
	while (tmp)
	{
		new = new_env(tmp->key, tmp->value);
		if (!new)
		{
			free_env(&list);
			return (NULL);
		}
		add_env(&list, new);
		if (tmp->next && ft_strcmp(tmp->next->value, "?") == 0)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (list);
}

// BUUUUUUUUUGGGED
void	swap_env(t_env **env, t_env *e1, t_env *e2)
{
	t_env	*tmp;
	t_env	*tmp2;

	if (!e1 || !e2 || e1 == e2)
		return ;
	ft_printf("head: %s\n", (*env)->key);
	if (e1 == *env)
		*env = e2;
	tmp = find_env(env, e1->key, 1);
	ft_printf("tmp: %s\n", tmp->key);
	tmp2 = find_env(env, e2->key, 1);
	ft_printf("tmp2: %s\n", tmp2->key);
	tmp2->next = e1;
	ft_printf("e1: %s\n", e1->key);
	if (tmp != e1)
		tmp->next = e2;
	ft_printf("e2: %s\n", e2->key);
	tmp2 = e2->next;
	ft_printf("tmp2: %s\n", tmp2->key);
	if (e2 != (*env))
		e2->next = e1;
	else
		e2->next = e1->next;
	ft_printf("e2: %s\n", e2->key);
	e1->next = tmp2;
	ft_printf("e1: %s\n", e1->key);
}

void	sort_env(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	t_env	**head;

	if (!env || !(*env) || !(*env)->next)
		return ;
	head = env;
	tmp1 = *env;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp1->key, tmp2->key) > 0)
			{
				printf("about to swap\n");
				swap_env(head, tmp1, tmp2);
				printf("swapped\n");
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

int	print_export(t_env **env, t_command *cmd, int out_fd)
{
	t_env	*cpy;

	cpy = copy_env(env);
	if (!cpy || !cmd)
		return (EXIT_FAILURE);
	ft_env(&cpy, NULL, 1);
	sort_env(&cpy);
	out_fd = 1;
	while (cpy)
	{
		ft_printf_fd(out_fd,
			"declare -x %s=\"%s\"\n",
			cpy->key, cpy->value);
		cpy = cpy->next;
	}
	printf("Get used to it\n");
	free_env(&cpy);
	return (EXIT_SUCCESS);
}

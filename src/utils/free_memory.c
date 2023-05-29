/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/29 12:35:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (*tokens != NULL)
	{
		tmp = *tokens;
		(*tokens) = (*tokens)->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
	free ((*tokens));
}

void	free_command(t_command **commands)
{
	t_command	*tmp;

	if (!commands || !*commands)
		return ;
	tmp = *commands;
	while (tmp->next != NULL)
		free_command(&(tmp->next));
	if (tmp->command)
		free(tmp->command);
	if (tmp->params)
		ft_free_array(&tmp->params, tmp->n_params);
	if (tmp->infile)
		free(tmp->infile);
	if (tmp->outfile)
		free(tmp->outfile);
	free (*commands);
	*commands = NULL;
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	tmp = *env;
	while (tmp->next != NULL)
		free_env(&(tmp->next));
	if (tmp->key)
		free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(*env);
	*env = NULL;
}

void	free_hrdc(t_heredoc **hrdc)
{
	t_heredoc	*tmp;

	if (!hrdc)
		return ;
	while ((*hrdc) != NULL)
	{
		tmp = *hrdc;
		(*hrdc) = (*hrdc)->next;
		free(tmp->line);
		free(tmp);
	}
	*hrdc = NULL;
}

void	ft_clear_everything(t_info g_info)
{
	if (g_info.tokens)
		free_tokens(&g_info.tokens);
	printf("1\n");
	if (g_info.commands)
		free_command(&g_info.commands);
	printf("2\n");
	// if (g_info.line)
	// 	free(g_info.line);
	printf("3\n");
	// if (g_info.fds)
	// 	free_int_array(g_info.fds);
	if (g_info.pids)
		free(g_info.pids);
	printf("4\n");
	 //exit_value =
}

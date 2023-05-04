/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:56:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/04 18:48:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_params(t_token *tokens, t_command *command, int get)
{
	static size_t	i;

	while (tokens->token_type == STRING && get)
	{
		command->params[i] = ft_strdup(tokens->content);
		if (!command->params[i++])
		{
			ft_free_array(&(command->params), i);
			return (FALSE);
		}
		tokens = tokens->next;
	}
	return ((int) i);
}

static t_token	*get_file_info(t_token *tokens, t_command *command)
{
	if (tokens->token_type == GREATER_THAN
		|| tokens->token_type == GREATER_GREATER)
	{
		command->outfile = ft_strdup(tokens->next->content);
		if (!command->outfile)
			command->check = 1;
		command->out_redirect = tokens->token_type;
	}
	else if (tokens->token_type == LESS_THAN || tokens->token_type == LESS_LESS)
	{
		command->infile = ft_strdup(tokens->next->content);
		if (!command->infile)
			command->check = 1;
		command->in_redirect = tokens->token_type;
	}
	return (tokens->next);
}

// Params is not allocated yet => param counting function between two commands 
// skipping redirects and the following (in/outfile))

t_token	*fill_command(t_token *tmp, t_command *command, int get)
{
	get = 1;
	if (tmp->token_type == COMMAND)
	{
		command->command = ft_strdup(tmp->content);
		if (!command->command)
			command->check = 1;
	}
	else if (tmp->token_type == STRING)
	{
		command->n_params = get_params(tmp, command, get);
		if (!command->n_params)
			command->check = 1;
	}
	else if (tmp->token_type == PIPE)
	{
		command->next = init_command(tmp->next);
		return (tmp);
	}
	else
		tmp = get_file_info(tmp, command);
	return (tmp->next);
}

t_command	*init_command(t_token *tokens)
{
	t_command	*command;
	t_token		*tmp;
	int			get;

	if (!tokens)
		return (NULL);
	tmp = tokens;
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
	{
		command->check = 1;
		return (NULL);
	}
	get = 0;
	while (tmp)
	{
		tmp = fill_command(tmp, command, get);
		if (command->check == 1) // not correct yet
		{
			free_command(&command);
			return (NULL);
		}
		get = 0;
	}
	return (command);
}

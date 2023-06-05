/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:56:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/02 12:50:28 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_params(t_token *token)
{
	int	n_params;

	n_params = 0;
	while (token && token->token_type != pipe_sym)
	{
		if (ft_isredir(token))
		{
			if (token->next->next)
			{
				token = token->next->next;
				continue ;
			}
			else
				return (n_params);
		}
		if (token->token_type == string || token->token_type == command_type)
			n_params++;
		token = token->next;
	}
	return (n_params);
}

void	get_params(t_token *token, t_command *command)
{
	int	i;

	command->n_params = count_params(token);
	command->params = ft_calloc(command->n_params + 1, sizeof(char *));
	i = 0;
	if (!command->params)
	{
		free_command(&command);
		ft_error(ENOMEM, "");
	}
	while (token && token->token_type != pipe_sym && i < command->n_params)
	{
		if (ft_isredir(token))
				token = token->next->next;
		command->params[i] = ft_strdup(token->content);
		if (!command->params[i++])
			free_command(&command);
		token = token->next;
	}
}

static t_token	*redir_command(t_token *token, t_command *command)
{
	if (token->token_type >= less_than)
	{
		if (command->infile)
			ft_free(command->infile);
		command->infile = ft_strdup(token->next->content);
		if (!command->infile)
			ft_error(ENOMEM, "");
		command->in_redirect = token->token_type;
	}
	else
	{
		if (command->outfile)
			free(command->outfile);
		command->outfile = ft_strdup(token->next->content);
		if (!command->outfile)
			ft_error(ENOMEM, "");
		command->out_redirect = token->token_type;
	}
	get_fds(command, token);
	return (token->next);
}

int	extract_command(t_token *token, t_command *command, int id)
{
	t_token		*tmp;
	int			params_flag;

	tmp = token;
	params_flag = 0;
	while (tmp)
	{
		if ((tmp->token_type == string || tmp->token_type == command_type)
			&& !params_flag)
		{
			get_params(token, command);
			params_flag = 1;
		}
		if (tmp->token_type == command_type)
		{
			command->command = ft_strdup(tmp->content);
			command->id = id++;
			if (!command->command)
				return (-1);
		}
		else if (tmp->token_type == pipe_sym)
		{
			command->next = init_command(tmp->next, id);
			return (0);
		}
		else if (tmp->token_type != string && tmp->token_type != command_type)
			tmp = redir_command(tmp, command);
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

t_command	*init_command(t_token *token, int id)
{
	t_command	*command;

	if (!token)
		return (NULL);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	if (extract_command(token, command, id) < 0)
	{
		free_command(&command);
		return (NULL);
	}
	return (command);
}

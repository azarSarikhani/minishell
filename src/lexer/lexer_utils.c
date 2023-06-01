/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/01 14:47:02 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

BOOL	redir_check(t_token *token)
{
	if (token && (token->token_type == GREATER_THAN
			|| token->token_type == GREATER_GREATER
			|| token->token_type == LESS_LESS
			|| token->token_type == LESS_THAN))
		return (TRUE);
	return (FALSE);
}

int	remove_quote(t_token **tokens)
{
	t_token	*temp;
	char	*tmp;

	temp = *tokens;
	while (temp != NULL)
	{
		if (temp->token_type == STRING)
		{
			if ((temp->content)[0] == '\'' || (temp->content)[0] == '\"')
			{
				tmp = ft_substr(temp->content, 1, ft_strlen(temp->content) - 2);
				if (tmp)
				{
					free(temp->content);
					temp->content = tmp;
					temp->isquote = 1;
				}
				else
					return (EXIT_FAILURE);
			}
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

void	remove_space(t_token **token)
{
	t_token	*temp;
	t_token	*previous;

	temp = *token;
	previous = temp;
	while (temp != NULL)
	{
		if (temp->token_type == SPACE)
		{
			if (temp == *token)
			{
				free(temp->content);
				*token = temp->next;
				free(previous);
			}
			else
			{
				free(temp->content);
				previous->next = temp->next;
				free (temp);
			}
		}
		previous = temp;
		temp = temp->next;
	}
}

t_token	*new_token(char *content, int token_type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		return (NULL);
	}
	new->token_type = token_type;
	new->next = NULL;
	return (new);
}

int	add_token(t_token **token, t_token *new, int *flag)
{
	t_token	*tmp;

	tmp = *token;
	if (new == NULL)
		*flag = -1;
	if (*token == NULL)
		*token = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (new->token_type == PIPE || new->token_type == LESS_THAN
		|| new->token_type == GREATER_THAN)
		return (1);
	return (EXIT_SUCCESS);
}

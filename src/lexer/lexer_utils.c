/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/12 12:44:54 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	add_token(t_token **token, t_token *new, int * flag)
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
	ft_printf("node's content : %s, node's type :%d\n", new->content, new->token_type);
	if (new->token_type == PIPE || new->token_type == LESS_THAN
		|| new->token_type == GREATER_THAN)
		return (1);
	return (EXIT_SUCCESS);
}

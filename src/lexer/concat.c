/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/02 12:38:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	concat_redir(t_token **token)
{
	t_token	*temp;

	if (((*token)->token_type == greater_than && (*token)->next->token_type
			== greater_than) || ((*token)->token_type == less_than
			&& (*token)->next->token_type == less_than))
	{
		ft_free((*token)->content);
		if ((*token)->token_type == greater_than)
		{
			(*token)->token_type = greater_greater;
			(*token)->content = ft_strdup(">>");
		}
		else
		{
			(*token)->token_type = less_less;
			(*token)->content = ft_strdup("<<");
		}
		if (!(*token)->content)
			return (EXIT_FAILURE);
		temp = (*token)->next;
		(*token)->next = (*token)->next->next;
		free(temp->content);
		free(temp);
	}
	return (EXIT_SUCCESS);
}

static	int	bzero_quote(t_token *token, t_token *next_token, char *temp
			, char *next_temp)
{
	if ((token->content)[0] == '\'' || (token->content)[0] == '\"')
	{
		temp = ft_substr(token->content, 1, ft_strlen(token->content) - 2);
		if (temp)
		{
			free(token->content);
			token->content = temp;
		}
		else
			return (EXIT_FAILURE);
	}
	if ((next_token->content)[0] == '\'' || (next_token->content)[0] == '\"')
	{
		next_temp = ft_substr(next_token->content, 1,
				ft_strlen(next_token->content) - 2);
		if (next_temp)
		{
			free(next_token->content);
			next_token->content = next_temp;
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	quote_check(t_token *token)
{
	if ((token->content)[0] == '\'' || (token->content)[0] == '\"'
			|| token->isquote == 1 || (token->next->content)[0] == '\''
			|| (token->next->content)[0] == '\"')
		return (1);
	return (0);
}

static int	merge_nodes(t_token *token, t_token *next_token, int quote)
{
	char	*temp;
	char	*tmp;
	char	*next_tmp;

	tmp = NULL;
	next_tmp = NULL;
	if (quote_check(token))
		if (bzero_quote(token, next_token, tmp, next_tmp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	temp = ft_strjoin(token->content, next_token->content);
	if (temp)
	{
		free(token->content);
		token->content = temp;
		token->next = token->next->next;
		token->isquote = quote;
		free(next_token->content);
		free(next_token);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

int	concatenate(t_token **tokens)
{
	t_token	*temp;
	int		quote;

	temp = *tokens;
	while (temp != NULL && temp->next != NULL)
	{
		if (concat_redir(&temp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		temp = temp->next;
	}
	temp = *tokens;
	while (temp != NULL && temp->next != NULL)
	{
		quote = 0;
		if (temp->token_type == string && temp->next->token_type == string)
		{
			quote = quote_check(temp);
			if (merge_nodes(temp, (temp->next), quote) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			temp = *tokens;
			continue ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

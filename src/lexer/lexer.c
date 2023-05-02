/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/02 14:15:33 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*expand_content(t_token **token, int start, t_env **env)
{
	int		end;
	int		i;
	char	*str;
	char	*new;

	end = start;
	i = 0;
	while (ft_isalnum((*token)->content[end]) && (*token)->content[end])
	{
		str[i] = (*token)->content[end];
		end++;
	}
	str = find_env(env, str);
	if (str)
	{
		i = ft_strlen((*token)->content) + 1;
		new = ft_calloc(i, 1);
		if (!new)
			return (NULL);
		new = replace_content((*token)->content, start, new, str);
		free((*token)->content);
		(*token)->content = new;
	}
	return ((*token)->content);
}

static	int	expander(t_token **tokens, t_env **env)
{
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '$')
			{
				if (tmp->content[0] != '\'')
					tmp->content = expand_content(&tmp, i, env);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

static	int	concatenate(t_token **tokens, t_env **env)
{
	t_token	*tmp;
	int		i;
	char	quote;

	tmp = *tokens;
	concatinate_redir(t_token **tokens);
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->content[i] == '\'' || tmp->content[i] == '\"' || i == 0
			|| temp->token_type == PIPE || temp->token_type == GREATER_THAN
			|| temp->token_type == LESS_THAN || temp->token_type == LESS_LESS
			| temp->token_type == GREATER_GREATER)
		{
			if (can_concat(temp))
			{
				//attach the content to the next node, point the next node to the next next node, get rid of this node(free it)
			}
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	init_lexer(char *line, t_token	**tokens)
{
	int		i;
	int		indicator;

	i = -1;
	while (line[++i])
	{
		indicator = i;
		if (line[i] == ' ' || line[i] == '\t')
			i += skip_white(&tokens, &line[i]);
		if (line[i] == '\"')
			i += get_string(&tokens, &line[i], '\"');
		if (line[i] == '\'')
			i += get_string(&tokens, &line[i], '\'');
		if (line[i] == '|')
			i += add_token(&tokens, new_token("|", PIPE));
		if (line[i] == '>')
			i += add_token(&tokens, new_token(">", GREATER_THAN));
		if (line[i] == '<')
			i += add_token(&tokens, new_token("<", LESS_THAN));
		if (ft_isprint(line[i]) && line[i] != '|' && line[i] != ';')
			i += get_command(&tokens, &line[i]);
		if (indicator > i)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	retokenizer(t_token **tokens, t_env **env)
{
	if (!expander(tokens, env))
		return (EXIT_FAILURE);
	if (!concatenate(tokens, env)) //concatinater
		return (EXIT_FAILURE);
	if (re_labler)
	return (EXIT_SUCCESS);
}

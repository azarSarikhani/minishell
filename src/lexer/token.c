/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/05 11:07:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_content(char **content, int start, int rm_end, char *str)
{
	int		i;
	int		old_len;
	int		end;
	int		len;
	char	*new;

	i = -1;
	end = ft_strlen(str);
	old_len = ft_strlen(*content);
	len = old_len - (rm_end - start) + end;
	new = ft_calloc(len + 1, 1);
	if (!new)
		return (EXIT_FAILURE);
	while (++i < start)
		new[i] = (*content)[i];
	end += i;
	old_len = i--;
	while (++i < end)
		new[i] = str[i - old_len];
	while (i < len)
		new[i++] = (*content)[rm_end++];
	free(*content);
	*content = new;
	return (EXIT_SUCCESS);
}

static int	re_label(t_token *temp)
{
	if (temp && !redir_check(temp))
		temp->token_type = command_type;
	else
		while (temp && redir_check(temp))
			temp = temp->next->next;
	if (temp)
		temp->token_type = command_type;
	while (temp != NULL)
	{
		if (temp->token_type == pipe_sym)
		{
			temp = temp->next;
			if (!redir_check(temp))
				temp->token_type = command_type;
			else
				while (temp && redir_check(temp))
					temp = temp->next->next;
			if (temp)
				temp->token_type = command_type;
		}
		if (temp)
			temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

static	int	expand_content(t_token **token, int start, t_env **env)
{
	int		end;
	char	*str;
	char	*value;

	end = start;
	while ((*token)->content[end] != ' ' && (*token)->content[end] != '\"'
		&& (*token)->content[end] != '\'' && (*token)->content[end])
		end++;
	str = ft_substr((*token)->content, start, end - start);
	if (!str)
		return (EXIT_FAILURE);
	value = find_value(env, str);
	if (replace_content(&((*token)->content), start - 1, end, value)
		== EXIT_SUCCESS)
	{
		free(str);
		return (EXIT_SUCCESS);
	}
	free(str);
	return (EXIT_FAILURE);
}

static	int	expand(t_token **tokens, t_env **env)
{
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '$' && tmp->content[0] != '\'')
			{
				if (expand_content(&tmp, i + 1, env) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	retokenize(t_token **tokens, t_env **env)
{
	if (expand(tokens, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (concatenate(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (remove_quote(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	remove_space(tokens);
	if (re_label(*tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

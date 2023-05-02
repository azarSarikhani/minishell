/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/02 14:14:11 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//comments ?
char	*replace_content(char *content, int start, char *new, char *str)
{
	int		i;
	int		end;
	int		j;
	int		len;

	i = -1;
	j = -1;
	end = ft_strlen(str);
	len = -1;
	while (++i < start)
		new[i] = content[++len];
	while (++i < end)
		new[i] = str[++j];
	end = ft_strlen(content);
	while (++i < end)
		new[i] = content[++len];
	new[i] = 0;
	return (new);
}

int	can_concat(t_token **token)
{
	t_token	*tmp;

	tmp = *tokens;
	if (tmp->next->token_type != SPACE || tmp->next->token_type != PIPE
		|| tmp->next->token_type != LESS_THAN
		|| tmp->next->token_type != GREATERTHAN
		|| tmp->next->token_type != LESS_LESS
		|| tmp->next->token_type != GREATER_GREATER)
		{
			return (1);
		}
	return (0);
}

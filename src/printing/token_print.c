/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:02:34 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/02 14:04:06 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	const char	*quotes[] = {
		">",
		">>",
		"<",
		"<<"
	};

	while (token)
	{
		if (token->token_type == string)
			ft_printf("string: %s\n", token->content);
		else if (token->token_type == command_type)
			ft_printf("cmd: %s\n", token->content);
		else if (token->token_type >= greater_than
			&& token->token_type <= less_less)
			ft_printf("%s\n", quotes[token->token_type - greater_than]);
		else if (token->token_type == pipe_sym)
			ft_printf("%s\n", token->content);
		else if (token->token_type == space)
			ft_printf("space: %s\n", token->content);
		printf("quote: %d\n", token->isquote);
		printf("-------------------\n");
		token = token->next;
	}
}

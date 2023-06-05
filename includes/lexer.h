/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/02 12:49:10 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define BOOL int

typedef struct s_token
{
	int				token_type;
	int				isquote;
	char			*content;
	struct s_token	*next;
}					t_token;

enum e_token_type
{
	string,
	command_type,
	greater_than,
	greater_greater,
	less_than,
	less_less,
	pipe_sym,
	space
};

t_token		*new_token(char *content, int token_type);
int			add_token(t_token **token, t_token *new, int *flag);
int			concatenate(t_token **tokens);
void		remove_space(t_token **token);
BOOL		redir_check(t_token *token);
int			remove_quote(t_token **tokens);

#endif
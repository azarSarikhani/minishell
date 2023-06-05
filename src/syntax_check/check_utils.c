/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/02 14:33:22 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_synt_error(char c)
{
	ft_putstr_fd("\033[1m\e[31mGayAsHell\x1b[m: syntax error near ", 2);
	if (c == '|')
		ft_putstr_fd("unexpected token `|', sis 💅\n", 2);
	else if (c == '<' || c == '>')
		ft_putstr_fd("unexpected token `newline', sis 💅\n", 2);
}

BOOL	check_first_last(char *line)
{
	int	last;

	if (line[0] == '|')
	{
		print_synt_error(line[0]);
		return (TRUE);
	}
	last = ft_strlen(line) - 1;
	if (line[last] == '>' || line[last] == '<'
		|| line [last] == '|')
	{
		print_synt_error(line[last]);
		return (TRUE);
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/02 13:36:12 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	closing_quote(char *line)
{
	int		i;
	char	quote;
	int		close_found;

	i = 0;
	close_found = 0;
	quote = line[0];
	while (line[++i] && !close_found)
	{
		if (line[i] == quote)
			close_found = 1;
	}
	if (close_found == 0)
	{
		ft_putstr_fd("GayAsHell: syntax error! Unclosed quotes.\n", 2);
		return (-1);
	}
	return (i);
}

static BOOL	quotes_close(char *line)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			result = closing_quote(&line[i]);
			if (result == -1)
				return (FALSE);
			i += result;
		}
		else
			i++;
	}
	return (TRUE);
}

static BOOL	empty_pipe(char *line)
{
	int		i;
	int		result;

	result = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i += skip_quoted_text(&line[i]);
		if ((line[i] == '|' && line[i + 1]))
		{
			result = skip_pipe(line, i);
			if (result == -1)
			{
				ft_putstr_fd("\033[1m\e[31mGayAsHell\x1b[m:  syntax error ", 2);
				ft_putstr_fd("near unexpected token `newline', sis 💅\n", 2);
				return (TRUE);
			}
			i += result;
		}
		else
			i++;
	}
	return (FALSE);
}

static BOOL	empty_redir(char *line)
{
	int		i;
	int		result;

	result = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i += skip_quoted_text(&line[i]);
		if ((line[i] == '>' || line[i] == '<') && line[i + 1])
		{
			result = skip_redir(&line[i]);
			if (result == -1)
			{
				ft_putstr_fd("\033[1m\e[31mGayAsHell\x1b[m:  syntax error ", 2);
				ft_putstr_fd("near Empty unexpected `newline', sis 💅\n", 2);
				return (TRUE);
			}
			i += result;
		}
		else
			i++;
	}
	return (FALSE);
}

BOOL	syntax_check(char *line)
{
	g_info.exit_value = 258;
	if (check_first_last(line))
		return (FALSE);
	if (!quotes_close(line))
		return (FALSE);
	if (empty_pipe(line))
		return (FALSE);
	if (empty_redir(line))
		return (FALSE);
	g_info.exit_value = 0;
	return (TRUE);
}

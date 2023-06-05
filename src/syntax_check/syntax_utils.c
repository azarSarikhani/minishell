/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/01 16:21:17 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quoted_text(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = line[0];
	while (line[++i])
	{
		if (line[i] == quote)
			break ;
	}
	return (i + 1);
}

static int	behind_pipe_empty(char *line, int i)
{
	while (--i >= 0)
	{
		if (ft_isprint(line [i]) && line[i] != ' ' && line[i]
			&& line[i] != '\t')
		{
			if (line[i] == '>' || line[i] == '<' || line[i] == '|')
				return (TRUE);
			else
				break ;
		}
	}
	if (i == 0)
		return (TRUE);
	return (FALSE);
}

static int	after_redir_empty(char *line)
{
	int		i;
	char	redir;

	redir = *line;
	i = 0;
	if (line[i + 1] == redir)
		i++;
	while (line[++i])
	{
		if (ft_isprint(line[i]) && line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] == '>' || line[i] == '<' || line[i] == '|')
				return (TRUE);
			else
				return (FALSE);
		}
	}
	if (line[i + 1] == 0)
		return (TRUE);
	return (FALSE);
}

int	skip_pipe(char *line, int i)
{
	if (behind_pipe_empty(line, i))
		return (-1);
	while (line[++i])
	{
		if (ft_isprint(line [i]) && line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] == '|')
				return (-1);
			if ((line[i] == '>' || line[i] == '<')
				&& after_redir_empty(&line[i]))
				return (-1);
			else
				break ;
		}
	}
	if (line[i] == 0)
		return (-1);
	return (1);
}

int	skip_redir(char *line)
{
	int		redir_count;
	char	redir;
	int		i;

	redir = line[0];
	redir_count = 1;
	i = 0;
	if (line[1] == 0)
		return (-1);
	if (line[1] == redir)
	{
		i++;
		redir_count++;
	}
	if (after_redir_empty(&line[i]))
		return (-1);
	return (redir_count);
}

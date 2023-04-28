/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:55:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/27 12:43:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	char		*command;
	char		**params;
	int			in_redirect;
	int			out_redirect;
	char		*infile;
	char		*outfile;
	int			in_fd[2];
	int			out_fd[2];
	t_command	*next;
}				t_command;

#endif
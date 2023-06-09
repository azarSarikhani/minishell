/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:49:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/12 11:33:19 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "parser.h"
# include <sys/wait.h>

# define READ 0
# define WRITE 1

typedef struct s_env
{
	char			*key;
	char			*value;
	int				print;
	struct s_env	*next;
}				t_env;

size_t		count_commands(t_command *commands);
int			get_exe_path(t_env **env, t_command *command);
void		exe_child(t_command *current, int **fds, int n_cmd, t_env *env);
int			**set_up_pipes(t_command *command, int n_cmd);
void		close_fds(int **fds, int cur, int n_cmd, int exe);
void		ft_wait(void);

#endif
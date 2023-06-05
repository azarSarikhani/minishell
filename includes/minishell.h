/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:50:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/05 13:46:39 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "syntax.h"
# include "redirect.h"
# include "lexer.h"
# include "redirect.h"
# include "ft_error.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0

# define NAME "\e[38;2;228;3;3mG\e[38;2;255;140;0ma\e[38;2;255;237;0my\
\e[38;2;0;128;38mA\e[38;2;36;64;182ms\e[38;2;120;61;150mH\x1b[m\
\e[38;2;245;169;184mel\x1b[ml\e[38;2;91;206;250m$>\x1b[m "

# define ON 1
# define OFF 0

typedef struct s_builtin
{
	char	*name;
	int		(*builtin)(t_env **, t_command *, int);
}		t_builtin;

typedef struct s_info
{
	t_token		*tokens;
	t_command	*commands;
	char		*line;
	int			**fds;
	int			*pids;
	int			n_cmd;
	int			exit_value;
	t_env		*env;
	int			n_cmd;
}		t_info;

t_info		g_info;

void		rl_replace_line(const char *text, int clear_undo);
void		init_env(char *envp[], t_env **env);
int			init_lexer(char *line, t_token	**tokens);
int			retokenize(t_token **tokens, t_env **env);
t_env		*find_env(t_env **env, char *variable, int predecessor);
char		**split_env(char *envp);
t_env		*new_env(char *key, char *value);
void		add_env(t_env **env, t_env *new);
t_env		*copy_env(t_env **env);
char		**ft_env_to_array(t_env *env);

char		*find_value(t_env **env, char *key);

//SYNTAX_CHECK AND TOKENIZE
int			init_lexer(char *line, t_token	**tokens);
int			retokenize(t_token **tokens, t_env **env);
BOOL		syntax_check(char *line);

//free
void		ft_clear_everything(t_info g_info);
void		free_tokens(t_token **tokens);
void		free_env(t_env **env);

//here_doc
int			here_doc(char	*delim);

//signal
void		init_signal(void);
void		heredoc_signal(void);
void		switch_echoctl(struct termios *t, int toggle);

int			redirect_exe(t_command *command, t_env *env);

// BUILTINS
int			is_builtin(t_command *cmd);
BOOL		exec_builtin(t_env **env, t_command *cmd, int out_fd);
int			ft_echo(t_env **env, t_command *cmd, int out_fd);
int			ft_env(t_env **env, t_command *cmd, int out_fd);
int			ft_pwd(t_env **env, t_command *cmd, int out_fd);
int			ft_cd(t_env **env, t_command *cmd, int out_fd);
int			ft_export(t_env **env, t_command *cmd, int out_fd);
int			print_export(t_env **env, t_command *cmd, int out_fd);
int			ft_unset(t_env **env, t_command *cmd, int out_fd);
void		print_token(t_token *token);

void		ft_clear(t_command **command, int **pids, int ***fds, int n_cmd);
#endif
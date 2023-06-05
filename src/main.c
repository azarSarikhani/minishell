/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/05 13:28:49 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	run_line(char *line, t_env **env)
{
	g_info.tokens = NULL;
	if (init_lexer(line, &g_info.tokens) == EXIT_FAILURE)
	{
		free_tokens(&g_info.tokens);
		return (EXIT_FAILURE);
	}
	if (retokenize(&g_info.tokens, env) == EXIT_FAILURE)
	{
		free_tokens(&g_info.tokens);
		return (EXIT_FAILURE);
	}
	g_info.commands = init_command(g_info.tokens, 0);
	if (g_info.exit_value == 0)
		redirect_exe(g_info.commands, *env);
	ft_clear_everything(g_info);
	return (0);
}

static	void	handle_exit(char *line)
{
	if (!line)
	{
		if (g_info.env)
			free_env(&g_info.env);
		write(2, "Sashay away\n", 12);
		exit(1);
	}
	if (ft_strcmp(line, "exit") == 0)
	{
		if (g_info.env)
			free_env(&g_info.env);
		write(2, "Sashay away\n", 12);
		g_info.exit_value = 0;
		free(line);
		exit(0);
	}
}

void	switch_echoctl(struct termios *t, int toggle)
{
	tcgetattr(STDIN_FILENO, t);
	if (toggle == OFF)
	{
		t->c_lflag &= ~(ECHOCTL);
		if (tcsetattr(STDIN_FILENO, TCSANOW, t) == -1)
			ft_putstr_fd("error in tcsetattr1\n", 2);
	}
	if (toggle == ON)
	{
		t->c_lflag |= ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, t) == -1)
			ft_putstr_fd("error in tcsetattr2\n", 2);
	}
}

static int	init_shell(t_env **env)
{
	struct termios	t;

	while (1)
	{
		switch_echoctl(&t, OFF);
		init_signal();
		g_info.line = readline(NAME);
		if (!g_info.line || ft_strcmp(g_info.line, "exit") == 0)
			handle_exit(g_info.line);
		switch_echoctl(&t, ON);
		if (ft_strlen(g_info.line) > 0)
		{
			if (g_info.line && *g_info.line)
				add_history(g_info.line);
			if (syntax_check(g_info.line))
				g_info.exit_value = run_line(g_info.line, env);
			if (g_info.exit_value == 258)
				free(g_info.line);
		}
	}	
	return (g_info.exit_value);
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_value;

	ft_bzero(&g_info, sizeof(t_info));
	(void)argv;
	if (argc > 1)
		return (-1);
	init_env(envp, &g_info.env);
	exit_value = init_shell(&g_info.env);
	return (exit_value);
}

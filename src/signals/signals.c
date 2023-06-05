/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/01 16:54:24 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_info.exit_value = 1;
	}
}

// static void	child_sig_handler(int sig, siginfo_t *info, void *context)
// {
// 	pid_t	pid;
// 	int		status;

// 	(void) context;
// 	(void) info;
// 	pid = waitpid(-1, &status, WNOHANG);
// 	if (sig == SIGQUIT)
// 	{
// 		if (pid == 0)
// 		{
// 			ft_putstr_fd("Quit: 3\n", 2);
// 			g_info.exit_value = 131;
// 		}
// 	}
// }

void	init_signal(void)
{
	struct sigaction	s_act;
	struct sigaction	s_quit;

	s_act.sa_handler = sigint_handler;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_act, NULL);
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_quit, NULL);
}

static	void	heredoc_handler(int sig)
{
	ft_clear_everything(g_info);
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_info.exit_value = 1;
	}
}

void	heredoc_signal(void)
{
	struct sigaction	s_act;
	struct sigaction	s_quit;

	s_act.sa_handler = heredoc_handler;
	sigemptyset(&s_act.sa_mask);
	s_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_act, NULL);
	sigaction(SIGTSTP, &s_act, NULL);
	sigaction(SIGQUIT, &s_quit, NULL);
}
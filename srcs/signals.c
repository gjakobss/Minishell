/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:22:47 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/02 16:30:02 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	if (g_mini.child == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		printf("^C\n");
}

void	sigquit_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	if (g_mini.child != 0)
		printf("^\\Quit: 3\n");
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	activate_signals(void)
{
	struct sigaction	sa_signal1;
	struct sigaction	sa_signal2;

	g_mini.sig_int = 0;
	tcgetattr(0, &g_mini.t);
	g_mini.t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &g_mini.t);
	sa_signal1.sa_sigaction = &sigint_handler;
	sa_signal2.sa_sigaction = &sigquit_handler;
	sigaction(SIGINT, &sa_signal1, NULL);
	sigaction(SIGQUIT, &sa_signal2, NULL);
}

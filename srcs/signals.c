/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:22:47 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/06 10:20:39 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	(void)signum;
	printf("\n");
	if (g_mini.child == 0)
	{
		rl_on_new_line();
//		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	activate_signals(void)
{
	struct termios		t;
	struct sigaction	sa_signal1;
	struct sigaction	sa_signal2;

	g_mini.sig_int = 0;
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	sa_signal1.sa_sigaction = &sig_handler;
	sa_signal2.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_signal1, NULL);
	sigaction(SIGQUIT, &sa_signal2, NULL);
}

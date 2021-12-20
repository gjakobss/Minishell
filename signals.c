/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:22:47 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/15 11:31:51 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	activate_signals(void)
{
	struct sigaction	sa_signal;

	g_mini.sig_int = 0;
	sa_signal.sa_sigaction = sig_handler;
	//	CTRL C;
	sigaction(SIGINT, &sa_signal, NULL);
	//	CTRL \;
	sigaction(SIGQUIT, &sa_signal, NULL);
}

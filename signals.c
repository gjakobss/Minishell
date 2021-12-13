/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:22:47 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/13 18:03:07 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int_signum, siginfo_t *info, void *context)
{

}

void	activate_signals(void)
{
	struct sigaction	sa_signal;

	sa_signal.sa_sigaction = sig_handler;
	//	CTRL C;
	sigaction(SIGINT, &sa_signal, NULL);
	//	CTRL \;
	sigaction(SIGQUIT, &sa_signal, NULL);
}

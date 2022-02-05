/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:25:38 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/05 17:25:41 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_ls(t_chars *x, int c)
{
	x->i = -1;
	while (g_mini.cmd[c].command[++x->i])
		x->sub = ft_str3join(x->sub, " ", g_mini.cmd[c].command[x->i]);
	x->temp = ft_str3join(x->sub, " ", x->temp);
	free(g_mini.cmd[c].command);
	g_mini.cmd[c].command = splitter(x->temp, ' ');
}

void	quotes_skipper(char *line, int *i, int quotes)
{
	if (quotes == DQUOTES)
	{
		(*i)++;
		while (line[*i] != '"' && line[*i] != '\0')
			(*i)++;
	}
	else if (quotes == SQUOTES)
	{
		(*i)++;
		while (line[*i] != '\'' && line[*i] != '\0')
			(*i)++;
	}
}

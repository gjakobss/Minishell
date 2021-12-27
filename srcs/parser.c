/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:52:03 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/27 12:03:34 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_terminator(char *line, int *j)
{
	if ((line[*j] == '>' && line[*j + 1] == '>')
		|| (line[*j] == '<' && line[*j + 1] == '<'))
		return (1);
	if (line[*j] == '|' || (line[*j] == '<' && line[*j - 1] != '<')
		|| (line[*j] == '>' && line[*j - 1] != '>') || line[*j] == ';')
		return (1);
	else
		return (0);
}

int	command_counter(char *line)
{
	int	counter;
	int	i;
	int	len;

	len = ft_strlen(line);
	counter = 1;
	i = 0;
	while (i < len)
	{
		if (line[i] == '"')
			g_mini.d_quotes += 1;
		if (line[i] == '\'')
			g_mini.s_quotes += 1;
		if (is_terminator(line, &i) && g_mini.d_quotes % 2 == 0
			&& g_mini.s_quotes % 2 == 0)
			counter++;
		i++;
	}
	g_mini.d_quotes = 0;
	g_mini.s_quotes = 0;
	return (counter);
}

t_cmds	*parser(char *line)
{
	t_cmds	*cmd;

	g_mini.num_cmds = command_counter(line);
	cmd = malloc(sizeof(t_cmds) * (g_mini.num_cmds + 1));
	lexer(cmd, line);
	expander(cmd);
	return (cmd);
}

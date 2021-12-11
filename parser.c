/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:52:03 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/11 23:13:20 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_terminator(char *line, int *j)
{
	if ((line[*j] == '>' && line[*j + 1] == '>') || (line[*j] == '<' && line[*j + 1] == '<')
		|| (line[*j] == '>' && line[*j - 1] == '>') || (line[*j] == '<' && line[*j - 1] == '<'))
	{
//		j += 1;
//		nao devia ser so uma das linhas de cima? Assim nao conta nunca quando sao >> ou <<
		return (0);
	}
	if (line[*j] == '|' || line[*j] == '<' || line[*j] == '>' || line[*j] == ';')
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
		if (is_terminator(line, &i))
			counter++;
		i++;
	}
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

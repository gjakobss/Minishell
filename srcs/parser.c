/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:52:03 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/06 15:28:40 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*correct_brackets(char *line)
{
	int		size;
	int		i;
	int		j;
	char	*str;

	size = ft_strlen(line);
	str = malloc(sizeof(char) * size);
	i = 0;
	j = 0;
	while (j < size)
	{
		if (line[j] == '{' || line[j] == '}')
			j++;
		str[i] = line[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	check_brackets_expansion(char **line)
{
	int		i;
	char	*str;

	i = 0;
	while ((*line)[i] && (*line)[i] != '$')
		i++;
	if ((*line)[i] == '\0')
		return ;
	else
	{
		if ((*line)[i + 1] == '{')
		{
			str = correct_brackets(*line);
			*line = NULL;
			*line = str;
		}
	}
	return ;
}

int	is_terminator(char *line, int j)
{
	if (line[j] == '>' && line[j + 1] == '>')
		return (1);
	if (line[j] == '|' || (line[j] == '<' && \
	line[j - 1] != '<' && line[j + 1] != '<')
		|| (line[j] == '>' && line[j - 1] != '>') || line[j] == ';')
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
		if (line[i] == '"' && g_mini.s_quotes % 2 == 0)
			g_mini.d_quotes += 1;
		if (line[i] == '\'' && g_mini.d_quotes % 2 == 0)
			g_mini.s_quotes += 1;
		if (is_terminator(line, i) && g_mini.d_quotes % 2 == 0
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
	int		i;

	check_brackets_expansion(&line);
	g_mini.num_cmds = command_counter(line);
	cmd = malloc(sizeof(t_cmds) * (g_mini.num_cmds + 1));
	lexer(cmd, line);
	i = -1;
	while (++i < g_mini.num_cmds)
		remove_middle_quotes(cmd[i].command);
	expander(cmd);
	i = -1;
	while (++i < g_mini.num_cmds)
		remove_beginning_quotes(cmd[i].command);
	return (cmd);
}

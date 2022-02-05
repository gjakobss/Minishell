/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:05:34 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/06 15:28:16 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_operator(char *line, int *i)
{
	if (line[*i] == '|')
		return (PIPE);
	else if (line[*i] == '\0')
		return (EOL);
	else if (line[*i] == '>')
	{
		if (line[*i + 1] == '>')
		{
			(*i)++;
			return (DGREATER);
		}
		else
			return (GREATER);
	}
	else if (line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			(*i)++;
			return (DSMALLER);
		}
		else
			return (SMALLER);
	}
	return (0);
}

static void	skip_quotes(char *line, int	*i)
{
	if (line[*i] == '"')
		quotes_skipper(line, i, DQUOTES);
	if (line[*i] == '\'')
		quotes_skipper(line, i, SQUOTES);
}

char	*assign_line2(int *i, char *line, t_cmds *cmd, int j)
{
	int	x;
	int	z;

	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		x = *i + 2;
		while (line[x] && line[x] == ' ')
			x++;
		z = x;
		while (line[z] && line[z] != ' ' && !is_terminator(line, z))
			z++;
		cmd[j].op = 5;
		cmd[j].heredoc = ft_strdup(ft_substr(line, x, (z - x)));
		line = ft_strdup(ft_strjoin(ft_substr(line, 0, *i), \
		ft_substr(line, z, (ft_strlen(line) - z))));
		*i -= 2;
	}
	return (line);
}

void	assign_line(t_cmds *cmd, char *line, int i, int j)
{
	int	start;
	int	len;

	while (line[++i])
	{
		start = i;
		while (line[i] && !is_terminator(line, i))
		{
			line = assign_line2(&i, line, cmd, j);
			skip_quotes(line, &i);
			i++;
		}
		len = i - start;
		if (cmd[j].op != 5)
			cmd[j].op = assign_operator(line, &i);
		else
			cmd[j].hdop = assign_operator(line, &i);
		if (len > 0)
			cmd[j].full_line = ft_substr(line, start, len);
		j++;
		if (line[i] == '\0')
			break ;
	}
	cmd[j].full_line = NULL;
}

void	lexer(t_cmds *cmd, char *line)
{
	int	i;

	assign_line(cmd, line, -1, 0);
	i = -1;
	while (++i < g_mini.num_cmds)
		cmd[i].command = splitter(cmd[i].full_line, ' ');
	cmd[i].command = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:52:03 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/10 13:32:22 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_terminator(char j)
{
	if (j == '|' || j == '<' || j == '>' || j == ';')
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
		if (is_terminator(line[i]))
			counter++;
		i++;
	}
	return (counter);
}

void	quotes_skipper(char *line, int	*i, int quotes)
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

void	assign_line(t_cmds *cmd, char *line)
{
	int	start;
	int	len;
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (line[++i])
	{
		start = i;
		while (line[i] && !is_terminator(line[i]))
		{
			if (line[i] == '"')
				quotes_skipper(line, &i, DQUOTES);
			if (line[i] == '\'')
				quotes_skipper(line, &i, SQUOTES);
			i++;
		}
		len = i - start;
		cmd[j].op = assign_operator(line, &i);
		if (len > 0)
			cmd[j].full_line = ft_substr(line, start, len);
		j++;
	}
	cmd[j].full_line = NULL;
}

void	expand_variable(char **line, int start)
{
	t_expand	str;
	int			i;
	int			len;

	(void)start;
	str.full = ft_strdup(*line);
	str.before = ft_substr(str.full, 0, start);
	i = start;
	while ((ft_isalpha(str.full[i]) || str.full[i] == '$') && str.full[i])
		i++;
	str.var = ft_substr(str.full, start, i + 1);
	// replace_var(&(str.var));
	len = ft_strlen(str.full);
	// str.after = ft_substr(str.full, i, len - i + 1);
	// juntar tudo com strjoins maybe?
}

void	expander(t_cmds *cmd)
{
	int	i;
	int	j;
	int	z;

	i = -1;
	while (++i < g_mini.num_cmds)
	{
		j = 0;
		while (cmd[i].command[++j])
		{
			z = -1;
			while (cmd[i].command[j][++z])
			{
				if (cmd[i].command[j][z] ==  '\'')
					while (cmd[i].command[j][++z] && cmd[i].command[j][z] != '\'')
						;
				if (cmd[i].command[j][z] == '$')
					expand_variable(&(cmd[i].command[j]), z);
			}
		}
	}
}

void	lexer(t_cmds *cmd, char *line)
{
	int	i;

	assign_line(cmd, line);
	i = -1;
	while (++i < g_mini.num_cmds)	
		cmd[i].command = ft_split(cmd[i].full_line, ' ');
	cmd[i].command = NULL;
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

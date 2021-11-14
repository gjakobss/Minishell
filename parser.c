/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:52:03 by malmeida          #+#    #+#             */
/*   Updated: 2021/11/08 12:21:02 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_terminator(char j)
{
//	if (j == '|' || j == '<' || j == '>' || j == ';' || j == '\0')
	if (j == '|' || j == '<' || j == '>' || j == ';')
	{
		if (j == '|')
		{
			g_mini.pipes += 1;
		}
		if (j == '\"')
			g_mini.d_quotes += 1;
		if (j == '\'')
			g_mini.s_quotes += 1;
		return (1);
	}
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
//		if (line[i] == '"')
//		{
//			i++;
//			while (line[i] != '"' && line[i])
//				i++;
//			i++;
//		}
		if (is_terminator(line[i]) && i > 0)
		{
			counter++;
//			i++;
//			if (is_terminator(line[i]))
//				i++;
		}
		i++;
	}
	return (counter);
}

void	assign_line(t_cmds *cmd, char *line)
{
	int	i;
	int	j;
	int	start;
	int	len;

	j = 0;
	i = 0;
	while (line[i])
	{
		start = i;
		while (!is_terminator(line[i]))
		{
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '"' && line[i] != '\0')
					i++;
			}
			if (line[i] == '\0')
				break;
			i++;
		}
		len = i - start;
		if (len > 0)
			cmd[j].full_line = ft_substr(line, start, len);
		j++;
		i++;
	}
}

int	check_commands(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))
			return (0);
		i++;
	}
	return (-1);
}

//1o aloca n structs t_cmds, sendo n o numero de comandos na line
//2o (assign_line) parte line em comandos, e mete cada comando dentro da sua struct
t_cmds	*parser(char *line)
{
	t_cmds	*cmd;
	int		num_cmds;
	int		i;

	if (check_commands(line) == -1)
		return (NULL);
	num_cmds = command_counter(line);
	cmd = malloc(sizeof(t_cmds) * (num_cmds + 1));
	assign_line(cmd, line);
	i = -1;
	while (++i < num_cmds)
	{
		cmd[i].command = ft_split(cmd[i].full_line, ' ');
	}
	cmd[i].command = NULL;
	return (cmd);
}


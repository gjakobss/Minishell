/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:52:03 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/07 12:24:13 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_terminator(char j)
{
	if (j == '"')
		g_mini.d_quotes += 1;
	else if (j == '\'')
		g_mini.s_quotes += 1;
	else if (j == '|' || j == '<' || j == '>' || j == ';')
	{
		if (j == '|')
			g_mini.pipes += 1;
		if (j == ';')
			g_mini.semi_col += 1;
		return (1);
	}
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
		{
			counter++;
		}
		i++;
	}
	return (counter);
}

void	skip_quotes(char *line, int *i)
{
	(*i)++;
	while (line[*i] != '"' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '"')
		g_mini.d_quotes += 1;
}

void	assign_line(t_cmds *cmd, char *line, int j, int i)
{
	int	start;
	int	len;

	while (line[++i])
	{
		start = i;
		while (!is_terminator(line[i]))
		{
			if (line[i] == '"')
				skip_quotes(line, &i);
			if (line[i] == '\0')
				break ;
			i++;
		}
		len = i - start;
		if (len > 0)
			cmd[j++].full_line = ft_substr(line, start, len);
	}
	cmd[j].full_line = NULL;
}

int	check_commands(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|' || line[i] == '<' || line[i] == '>' || line[i] == ';' || line[i] == ' ')
		{
			while (line[i] != '\0')
			{
				if ((line[i] >= 'a' && line[i] <= 'z')
					|| (line[i] >= 'A' && line[i] <= 'Z'))
					break;
			i++;
			}
			if (line[i] == '\0')
			{
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

void	expand_variables(char *line)
{
	int		i;
	int		start;
	char	*new;
	char	*var;

	var = NULL;
	new = line;
	i = 0;
	while (new[i] != '$' && new[i] != '\0')
		i++;
	if (new[i] == '\0')
		return ;
	if (new[i] == '$')
	{
		start = i;
		while (new[i] != ' ' && new[i] != '\0' && new[i] != '"')
			i++;
		var = ft_substr(line, start, i - start);
	}
	printf("%s\n", var);

}
/*
void	parse_args(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_mini.num_cmds)
	{
		j = 1;
		while (g_mini.cmd[i].command[j] != NULL)
		{
			if (g_mini.cmd[i].command[j][0] == '"')
			{
				printf("EEEY\n");
				expand_variables(g_mini.cmd[i].command[j]);
		//		remove_aspas(&(g_mini->cmd[i]->command[j]));
			}
			else if (g_mini.cmd[i].command[j][0] == '\'')
		//		remove_clicas(&(g_mini->cmd[i]->command[j]));
			j++;
		}
		i++;
	}
}
*/
//1o aloca n structs t_cmds, sendo n o numero de comandos na line
//2o (assign_line) parte line em comandos, e mete cada comando dentro da sua struct
t_cmds	*parser(char *line)
{
	t_cmds	*cmd;
	int		i;

//	line = ft_strjoin(line, "'\0");
	if (check_commands(line) == -1)
		return (NULL);
	g_mini.num_cmds = command_counter(line);
	cmd = malloc(sizeof(t_cmds) * (g_mini.num_cmds + 1));
	assign_line(cmd, line, 0, -1);
	i = -1;
	while (++i < g_mini.num_cmds)	
		cmd[i].command = ft_split(cmd[i].full_line, ' ');
	cmd[i].command = NULL;
	if (((g_mini.s_quotes / 2) % 2 != 0) || ((g_mini.d_quotes / 2) % 2 != 0))
	{
		printf("Error: unclosed quotes\n");
		return (NULL);
	}
	return (cmd);
}

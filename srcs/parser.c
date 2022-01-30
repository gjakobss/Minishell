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

int	is_terminator(char *line, int j)
{
	if (line[j] == '>' && line[j + 1] == '>')
		return (1);
	if (line[j] == '|' || (line[j] == '<' && line[j - 1] != '<' && line[j + 1] != '<')
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

void    remove_beginning_quotes(char **cmd)
{
    int     i;
    int     j;
    char    **ptr;
    
    i = 0;
    while (cmd[i])
    {
        if (cmd[i][0] == '"')
        {
            ptr = ft_split(cmd[i], '"');
            j = 1;
            while (ptr[j] != NULL)
                ptr[0] = ft_strjoin(ptr[0], ptr[j++]);
            cmd[i] = ptr[0];
        }
        if (cmd[i][0] == '\'')
        {
            ptr = ft_split(cmd[i], '\'');
            j = 1;
            while (ptr[j] != NULL)
                ptr[0] = ft_strjoin(ptr[0], ptr[j++]);
            cmd[i] = ptr[0];
        }
        i++;
    }
}

void    remove_middle_quotes(char **cmd)
{
    int     i;
    int     j;
    int     z;
    char    **ptr;

    i = 0;
    while (cmd[i])
    {
        j = 0;
        while (cmd[i][j])
        {
            if (cmd[i][j] == '"' && cmd[i][j + 1] == '"')
            {
                ptr = ft_split(cmd[i], '"');
                z = 1;
                while (ptr[z] != NULL)
                    ptr[0] = ft_strjoin(ptr[0], ptr[z++]);
                cmd[i] = ptr[0];
            }
            if (cmd[i][j] == '\'' && cmd[i][j + 1] == '\'')
            {
                ptr = ft_split(cmd[i], '\'');
                z = 1;
                while (ptr[z] != NULL)
                    ptr[0] = ft_strjoin(ptr[0], ptr[z++]);
                cmd[i] = ptr[0];
            }
            j++;
        }
        i++;
    }
}

t_cmds	*parser(char *line)
{
	t_cmds	*cmd;
    int     i;

	g_mini.num_cmds = command_counter(line);
	cmd = malloc(sizeof(t_cmds) * (g_mini.num_cmds + 1));
	lexer(cmd, line);
	expander(cmd);
    i = -1;
    while (++i < g_mini.num_cmds)
    {
        remove_beginning_quotes(cmd[i].command);
        remove_middle_quotes(cmd[i].command);
    }
    return (cmd);
}

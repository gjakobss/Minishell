/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:09:56 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/06 10:29:55 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_command(char **line, t_expand str)
{
	char	*half;
	char	*full;

	half = ft_strjoin(str.before, str.var);
	full = ft_strjoin(half, str.after);
	*line = NULL;
	*line = ft_strdup(full);
}

void	replace_var(char **str)
{
	int		i;
	int		j;
	int		len;
	char	*copy;

	copy = ft_substr(*str, 1, 100);
	len = ft_strlen(copy);
	i = -1;
	while (g_mini.env[++i])
		if (ft_strncmp(copy, g_mini.env[i], len - 1) == 0)
			break ;
	if (ft_strncmp(copy, g_mini.env[i], len - 1) == 0)
	{
		*str = NULL;
		j = 0;
		while (g_mini.env[i][j] != '=')
			j++;
		*str = ft_substr(g_mini.env[i], j + 1, 100);
	}
	else
	{
		*str = NULL;
		*str = malloc(sizeof(char));
		*str[0] = '\0';
	}
}

void	expand_variable(char **line, int start)
{
	t_expand	str;
	int			i;
	int			len;

	(void)start;
	str.full = ft_strdup(*line);
	if (str.full[start] == '$' && str.full[start + 1] == '?')
	{
		*line = ft_itoa(g_mini.status);
		g_mini.status = 0;
		return ;
	}
	str.before = ft_substr(str.full, 0, start);
	i = start;
	while ((ft_isalpha(str.full[i]) || str.full[i] == '$') && str.full[i])
		i++;
	str.var = ft_substr(str.full, start, i - start);
	replace_var(&(str.var));
	len = ft_strlen(str.full);
	str.after = ft_substr(str.full, i, len - i);
	replace_command(line, str);
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
				if (cmd[i].command[j][z] == '\'' && cmd[i].command[j][z - 1] != '"')
					while (cmd[i].command[j][++z]
					&& cmd[i].command[j][z] != '\'')
					;
				if (cmd[i].command[j][z] == '$')
					expand_variable(&(cmd[i].command[j]), z);
			}
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:09:56 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/07 12:27:19 by malmeida         ###   ########.fr       */
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

char	*replace_var(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*copy;

	copy = ft_substr(str, 1, 250);
	len = ft_strlen(copy);
	i = -1;
	if (len == 1)
	{
		while (g_mini.env[++i])
			if (copy[0] == g_mini.env[i][0] && (g_mini.env[i][1] == '='|| g_mini.env[i][1] == '\0'))
				break;
	}
	else
	{
		while (g_mini.env[++i])
			if (ft_strncmp(copy, g_mini.env[i], len - 1) == 0)
				break ;
	}
	if (g_mini.env[i] == NULL)
		return (NULL);
	if (ft_strncmp(copy, g_mini.env[i], len - 1) == 0)
	{
		str = NULL;
		j = 0;
		while (g_mini.env[i][j] != '\0' && g_mini.env[i][j] != '=')
			j++;
		str = ft_substr(g_mini.env[i], j + 1, 250);
	}
	else
	{
		str = NULL;
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	return (str);
}

void	more_than_one_var(t_expand	str, char **line)
{
	int	i;
	int	j;

	i = 0;
	str.var = ft_strdup("");
	while (str.full[i])
	{
		if (str.full[i] == '$')
		{
			j = i + 1;
			while (str.full[j] && str.full[j] != '$')
				j++;
			str.var = ft_strjoin(str.var, replace_var(ft_substr(str.full, i, j - i)));
		}
		i++;
	}
	str.after = ft_strdup("");
	replace_command(line, str);
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
		return ;
	}
	str.before = ft_substr(str.full, 0, start);
	i = start;
	while ((ft_isalpha(str.full[i])) && str.full[i])
		i++;
//fazer este while dentro do more_than_one_var para poupar linhas e nao estragar o i
	while (str.full[i++])
		if (str.full[i] == '$')
		{
			more_than_one_var(str, line);
			return ;
		}
	str.var = ft_substr(str.full, start, i - start + 1);
	str.var = replace_var(str.var);
	if (!str.var)
	{
		*line = NULL;
		return ;
	}
	len = ft_strlen(str.full);
	str.after = ft_substr(str.full, i, len - i);
	replace_command(line, str);
}

void	safety_check(char	**str, int j)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (++i < j)
	{
		if (str[i] == NULL)
		{
			counter = i;
			while (i < j && str[i] == NULL)
				i++;
			if (i < j)
			{
				str[counter] = str[i];
				str[i] = NULL;
				i = counter;
			}
		}
	}
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
				if (cmd[i].command[j][z] == '\'' && cmd[i].command[j][0] != '"')
					while (cmd[i].command[j][++z]
					&& cmd[i].command[j][z] != '\'')
					;
				if (cmd[i].command[j][z] == '$')
					expand_variable(&(cmd[i].command[j]), z);
				if (cmd[i].command[j] == NULL)
					break ;
				if (cmd[i].command[j][z] == '\0')
					break ;
			}
		}
		safety_check((cmd[i].command), j);
	}
}

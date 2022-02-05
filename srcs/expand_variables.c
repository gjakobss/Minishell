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
			if (copy[0] == g_mini.env[i][0] && (g_mini.env[i][1] == '=' \
			|| g_mini.env[i][1] == '\0'))
				break ;
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

void static	expand_helper(t_expand *str, int *i)
{
	str->var = ft_itoa(g_mini.status);
	*i += 2;
}

void	expand_variable(char **line, int start)
{
	t_expand	str;
	int			i;
	int			len;

	str.full = ft_strdup(*line);
	str.before = ft_substr(str.full, 0, start);
	i = start;
	if (str.full[start] == '$' && str.full[start + 1] == '?')
		expand_helper(&str, &i);
	else
	{
		while (str.full[i] && (ft_isalpha(str.full[++i])))
			i++;
		str.var = ft_substr(str.full, start, i - start + 1);
		str.var = replace_var(str.var);
		if (!str.var)
		{
			*line = NULL;
			return ;
		}
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
	t_vars	var;
	
	var.i = -1;
	while (++var.i < g_mini.num_cmds)
	{
		var.j = 0;
		while (cmd[var.i].command[++var.j])
		{
			var.size = ft_strlen(cmd[var.i].command[var.j]);
			var.z = -1;
			while (cmd[var.i].command[var.j][++var.z])
			{
				if (cmd[var.i].command[var.j][var.z] == '\'' && cmd[var.i].command[var.j][0] != '"')
					while (cmd[var.i].command[var.j][++var.z]
					&& cmd[var.i].command[var.j][var.z] != '\'')
					;
				if (cmd[var.i].command[var.j][var.z] == '$')
					expand_variable(&(cmd[var.i].command[var.j]), var.z);
				if (var.size == 1 && var.z == 0 && cmd[var.i].command[var.j][var.z] && \
				cmd[var.i].command[var.j][var.z] == '~')
					cmd[var.i].command[var.j] = get_env("HOME");
				if (cmd[var.i].command[var.j] == NULL)
					break ;
				if (cmd[var.i].command[var.j][var.z] == '\0')
					break ;
			}
		}
		safety_check((cmd[var.i].command), var.j);
	}
}

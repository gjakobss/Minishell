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

void static	expander_helper(t_cmds *cmd, t_vars *v)
{
	if (cmd[v->i].command[v->j][v->z] == '\'' && \
	cmd[v->i].command[v->j][0] != '"')
		while (cmd[v->i].command[v->j][++v->z] && \
		cmd[v->i].command[v->j][v->z] != '\'')
			;
	if (cmd[v->i].command[v->j][v->z] == '$')
		expand_variable(&(cmd[v->i].command[v->j]), v->z);
}

void	expander(t_cmds *cmd)
{
	t_vars	v;

	v.i = -1;
	while (++v.i < g_mini.num_cmds)
	{
		v.j = 0;
		while (cmd[v.i].command[++v.j])
		{
			v.size = ft_strlen(cmd[v.i].command[v.j]);
			v.z = -1;
			while (cmd[v.i].command[v.j][++v.z])
			{
				expander_helper(cmd, &v);
				if (v.size == 1 && v.z == 0 && cmd[v.i].command[v.j][v.z] \
				&& cmd[v.i].command[v.j][v.z] == '~')
					cmd[v.i].command[v.j] = get_env("HOME");
				if (cmd[v.i].command[v.j] == NULL)
					break ;
				if (cmd[v.i].command[v.j][v.z] == '\0')
					break ;
			}
		}
		safety_check((cmd[v.i].command), v.j);
	}
}

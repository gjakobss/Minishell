/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:09:56 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/11 23:16:00 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	str.var = ft_substr(str.full, start, i - start);
	// replace_var(&(str.var));
	len = ft_strlen(str.full);
	str.after = ft_substr(str.full, i, len - i);
	printf("full str is: %s\n", str.full);
	printf("before is: %s\n", str.before);
	printf("var is: %s\n", str.var);
	printf("after is %s\n", str.after);
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

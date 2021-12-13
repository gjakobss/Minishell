/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:09:56 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/13 12:50:02 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_var(char **str)
{
	int		i;
	int		j;
	int		len;
	char	*copy;

	copy = ft_strdup(*str);
	len = ft_strlen(copy);
	i = 0;
	while (g_mini.env[i])
	{
		if (ft_strncmp(copy, g_mini.env[i], len - 1) == 0)
			break;
		i++;
	}
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
	str.before = ft_substr(str.full, 0, start);
	i = start;
	while ((ft_isalpha(str.full[i]) || str.full[i] == '$') && str.full[i])
		i++;
	str.var = ft_substr(str.full, start, i - start);
	replace_var(&(str.var));
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

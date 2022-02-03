/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:10:20 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/03 16:10:28 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_remover(char **cmd, int *i, int quotes)
{
	int		z;
	char	**ptr;

	if (quotes == DQUOTES)
	{
		ptr = ft_split(cmd[*i], '"');
		z = 1;
		while (ptr[z] != NULL)
			ptr[0] = ft_strjoin(ptr[0], ptr[z++]);
		cmd[*i] = ptr[0];
	}
	if (quotes == SQUOTES)
	{
		ptr = ft_split(cmd[*i], '\'');
		z = 1;
		while (ptr[z] != NULL)
			ptr[0] = ft_strjoin(ptr[0], ptr[z++]);
		cmd[*i] = ptr[0];
	}
}

void	remove_middle_quotes(char **cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '"' && cmd[i][j + 1] == '"')
				quote_remover(cmd, &i, DQUOTES);
			if (cmd[i][j] == '"' && cmd[i][j + 1] != '\0')
			{
				j++;
				while (cmd[i][j] && cmd[i][j] != '"')
					j++;
			}
			if (cmd[i][j] == '\'' && cmd[i][j + 1] == '\'')
				quote_remover(cmd, &i, SQUOTES);
			j++;
		}
		i++;
	}
}

void	remove_beginning_quotes(char **cmd)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '"')
		{
			flag = 1;
			quote_remover(cmd, &i, DQUOTES);
		}
		if (cmd[i][0] == '\'' && flag == 0)
			quote_remover(cmd, &i, SQUOTES);
		i++;
	}
}

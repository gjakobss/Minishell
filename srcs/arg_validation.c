/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:22:40 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/15 13:00:21 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_commands(char **line)
{
	int	i;

	i = 0;
	while (line[0][i] != '\0')
	{
		if (line[0][i] == '|' || line[0][i] == '<' || line[0][i] == '>'
			|| line[0][i] == ';' || line[0][i] == ' ' || line[0][i] == '	')
		{
			while (line[0][i] != '\0')
			{
				if ((line[0][i] >= 'a' && line[0][i] <= 'z')
					|| (line[0][i] >= 'A' && line[0][i] <= 'Z'))
				{
					line[0] = ft_substr(line[0], i, ft_strlen(line[0]) - 1);
					break ;
				}
				i++;
			}
			if (line[0][i] == '\0')
				return (1);
		}
		if ((line[0][i] >= 'a' && line[0][i] <= 'z')
			|| (line[0][i] >= 'A' && line[0][i] <= 'Z'))
			break ;
		i++;
	}
	return (0);
}

void	operators_count(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (is_quote(line[i]))
		{
			while (!is_quote(line[++i]))
				if (line[i] == '\0')
					return ;
		}
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			g_mini.pipes += 1;
		if (line[i] == ';')
			g_mini.semi_col += 1;
	}
}

int	quotes_checker(char *line)
{
	int	i;
	int	quote;

	g_mini.d_quotes = 0;
	g_mini.s_quotes = 0;
	i = -1;
	while (line[++i])
	{
		quote = is_quote(line[i]);
		if (quote == DQUOTES && g_mini.s_quotes % 2 == 0)
			g_mini.d_quotes += 1;
		if (quote == SQUOTES && g_mini.d_quotes % 2 == 0)
			g_mini.s_quotes += 1;
	}
	if ((g_mini.s_quotes % 2 != 0) || (g_mini.d_quotes % 2 != 0))
		return (1);
	else
		return (0);
}


int	arg_validation(char **line)
{
	if (check_commands(line))
	{
		printf("");
		return (1);
	}
	if (quotes_checker(*line))
	{
		printf("Error: Unclosed quotes\n");
		return (1);
	}
	operators_count(*line);
	return (0);
}

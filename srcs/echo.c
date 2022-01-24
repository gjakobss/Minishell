/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:15 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/07 14:07:54 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*real_aspas_remover(char *str)
{
	char	**ptr;
	int		i;
	char	c;

	i = -1;
	c = '"';
	while (str[++i])
	{
		if (str[i] == '"')
			break ;
		else if (str[i] == '\'')
		{
			c = '\'';
			break ;
		}
	}
	if (str[i] == '\0')
		return (str);
	else
		ptr = ft_split(str, c);
	i = 1;
	while (ptr[i] != NULL)
		ptr[0] = ft_strjoin(ptr[0], ptr[i++]);
	return (*ptr);
}

static void	aspas_remover(char **str, int n_flag)
{
	int		i;

	if (n_flag)
		i = 2;
	else
		i = 1;
	while (str[i])
	{
		if ((str[i][0] == '\'' && str[i][1] == '\'') || \
				(str[i][0] == '"' && str[i][1] == '"'))
			str[i] = NULL;
		else
			str[i] = real_aspas_remover(str[i]);
		i++;
	}
}

int	bi_echo(char **str)
{
	int	n_flag;
	int	i;

	if (str[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	n_flag = 0;
	i = 0;
	if (str[1][0] == '-' && str[1][1] == 'n')
	{
		n_flag = 1;
		i = 1;
	}
    if (str[1][0] == '~' && str[1][1] == '\0')
    {
        printf("%s\n", getenv("HOME"));
        return (0);
    }
	aspas_remover(str, n_flag);
	while (str[++i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

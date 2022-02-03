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

int	bi_echo2(int x, char **str)
{
	if (g_mini.cmd[x].op == 3 && access(str[1], F_OK) == -1)
	{
		printf("echo: %s: no such file or directory\n", str[1]);
		return (0);
	}
	else if (g_mini.cmd[x].op == 3 && access(str[1], F_OK) == 0)
	{
		printf("\n");
		return (0);
	}
	if (str[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	if (str[1][0] == '~' && str[1][1] == '\0')
	{
		printf("%s\n", getenv("HOME"));
		return (0);
	}
	return (1);
}

int	bi_echo(int x, char **str)
{
	int	n_flag;
	int	i;

	if (bi_echo2(x, str) == 0)
		return (0);
	n_flag = 0;
	i = 0;
	if (str[1][0] == '-' && str[1][1] == 'n')
	{
		n_flag = 1;
		i = 1;
	}
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

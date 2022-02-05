/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:55:24 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/05 13:55:26 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_export(void)
{
	int	i;

	i = 0;
	while (g_mini.exp[i])
		printf("declare -x %s\n", g_mini.exp[i++]);
	return ;
}

void	get_new_env(char **buff, int i, int j)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (g_mini.env[++i] != NULL)
		new_env[i] = ft_strdup(g_mini.env[i]);
	new_env[i++] = ft_strdup(buff[j]);
	new_env[i] = NULL;
	i = 0;
	free(g_mini.env);
	g_mini.env = new_env;
}

int	ft_strchrlen(char	*str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	exit_helper(int j, int i)
{
	if (j == 257)
	{
		printf("bash: exit: numeric argument required\n");
		exit(garbage_collector(255));
	}
	else if (i > 2)
		printf("bbshell: exit: too many arguments\n");
	else
		printf("exit\n");
}

void	safety_check(char **str, int j)
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

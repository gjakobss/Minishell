/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:49:18 by gjakobss          #+#    #+#             */
/*   Updated: 2021/12/18 18:49:20 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_env_from_export(char **buff, int j)
{
	int		i;
	int		checker;

	i = -1;
	checker = 0;
	while (buff[++j] != NULL)
		if (ft_strchr(buff[j], 61) != NULL)
			break ;
	if (buff[j] == NULL)
		return (j);
	else
	{
		while (buff[j][checker] != '=')
			checker++;
		while (g_mini.env[++i] != NULL)
		{
			if (ft_strncmp(buff[j], g_mini.env[i], checker) == 0)
			{
				g_mini.env[i] = buff[j];
				return (j);
			}
		}
	}
	get_new_env(buff, i, j);
	return (j);
}

int	bi_export2(int j, int i, char **buff)
{
	int	checker;

	checker = 0;
	while (buff[j][checker] != '\0' && buff[j][checker] != '=')
		checker++;
	while (g_mini.exp[++i])
	{
		if (ft_strncmp(buff[j], g_mini.exp[i], checker) == 0)
		{
			checker = -1;
			g_mini.exp[i] = buff[j];
			g_mini.exp = exp_organizer(g_mini.exp, NULL, 0, 0);
			break ;
		}
	}
	if (checker != -1)
		g_mini.exp = exp_organizer(g_mini.exp, buff[j], 0, 0);
	return (j);
}

int	bi_export(char **buff)
{
	int	j;
	int	i;

	j = 0;
	i = -1;
	if (!buff[1])
	{
		write_export();
		return (0);
	}
	while (buff[++j] != NULL)
		j = bi_export2(j, i, buff);
	j = 0;
	while (buff[j] != NULL)
		j = get_env_from_export(buff, j);
	return (0);
}

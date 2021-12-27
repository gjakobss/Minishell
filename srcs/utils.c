/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:18:09 by gjakobss          #+#    #+#             */
/*   Updated: 2021/12/27 12:14:24 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_quotes(char **exp, char *str, int z)
{
	int		i;
	int		j;
	int		x;
	char	**ret;

	i = 0;
	while (exp[i])
		i++;
	if (str)
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	j = 0;
	i = 0;
	x = -1;
	if (str)
	{
		ret[j] = malloc(sizeof(char) * (ft_strlen(str) + 3));
		while (str[++x])
		{
			ret[j][i] = str[x];
			if (str[x] == '=')
			{
				z = 1;
				ret[j][++i] = '"';
			}
			i++;
		}
		if (z == 1)
			ret[j][i++] = '"';
		ret[j][i] = '\0';
		j++;
	}
	i = -1;
	x = -1;
	while (exp[++x] != NULL)
	{
		z = -1;
		ret[j] = malloc(sizeof(char) * (ft_strlen(exp[x]) + 3));
		while (exp[x][++z])
		{
			ret[j][++i] = exp[x][z];
			if (exp[x][z] == '=' && exp[x][z + 1] != '"')
				ret[j][++i] = '"';
		}
		if (ret[j][i] != '"')
			ret[j][++i] = '"';
		i++;
		ret[j][i] = '\0';
		j++;
		i = -1;
	}
	ret[j] = NULL;
	return (ret);
}

char	*exp_organizer2(char **ret, int i)
{
	int	j;
	int	x;

	j = 0;
	while (ret[++j] != NULL)
	{
		if (i == j)
			j++;
		if (ret[j] == NULL)
			break ;
		if (ret[i][0] > ret[j][0] && ft_strcmp(ret[j], "0") != 0)
			i = j;
		else if (ret[i][0] == ret[j][0] && ft_strcmp(ret[j], "0") != 0)
		{
			x = 0;
			while (ret[i][x] != '\0' && ret[j][x] != '\0'
			&& ret[i][x] == ret[j][x])
				x++;
			if (ret[j][x] == '\0' || ret[i][x] > ret[j][x])
				i = j;
		}
	}
	return (ret[i]);
}

char	**exp_organizer(char **exp, char *str, int i, int y)
{
	char	**ret;
	int		j;

	while (exp[i])
		i++;
	if (str != NULL)
		i++;
	ret = get_quotes(exp, str, 0);
	exp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ret[i] != NULL)
	{
		j = 0;
		exp[y] = exp_organizer2(ret, i);
		while (ft_strcmp(ret[j], exp[y]) != 0)
			j++;
		if (ft_strcmp(ret[j], exp[y]) == 0)
			ret[j] = "0";
		y++;
		while (ret[i] != NULL && ft_strcmp(ret[i], "0") == 0)
			i++;
	}
	exp[y] = NULL;
	return (exp);
}

int	exec_one_bi(int x)
{
	char	*str;

	str = g_mini.cmd[x].command[0];
	if (!ft_strcmp(str, "cd"))
		return(bi_cd(g_mini.cmd[x].command[1]));
	if (!ft_strcmp(str, "pwd"))
		return(bi_pwd());
	if (!ft_strcmp(str, "env"))
		return(bi_env());
	if (!ft_strcmp(str, "echo"))
		return(bi_echo(g_mini.cmd[x].command));
	if (!ft_strcmp(str, "export"))
		return(bi_export(g_mini.cmd[x].command));
	if (!ft_strcmp(str, "unset"))
		return(bi_unset(g_mini.cmd[x].command));
	return (-1);
}

int	is_builtin(int x)
{
	char	*str;

	str = g_mini.cmd[x].command[0];
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "cd"))
		return (1);
	return (0);
}

int	get_bin_path(void)
{
	int	i;

	i = -1;
//	usar o getenv("PATH")
	while (g_mini.env[++i] != NULL)
		if (g_mini.env[i][0] == 'P' && g_mini.env[i][1] == 'A')
			break ;
	if (g_mini.env[i] == NULL && is_builtin(0) == 0)
		return (-1);
	else if (g_mini.env[i] == NULL && is_builtin(0) == 1)
		return (0);
	g_mini.bin_paths = ft_split(g_mini.env[i] + 5, ':');
	return (0);
}

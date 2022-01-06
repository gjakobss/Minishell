/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:18:09 by gjakobss          #+#    #+#             */
/*   Updated: 2022/01/06 15:30:52 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

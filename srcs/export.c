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

int	ft_strchrlen(char	*str, char c)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	check_if_valid(char **buff, int j, int index)
{
	int i;

	i = 0;
	if (buff[j][i] != '_' && ft_isalpha(buff[j][i]) == 0)
	{
		if (index == 2)
			printf("bbshell: export: '%s': not a valid identifier\n", ft_substr(buff[j], 0, ft_strchrlen(buff[j], '=')));
		return (-1);
	}
	while (buff[j][++i] && buff[j][i] != '=')
	{
		if (ft_isalnum(buff[j][i]) == 0 && buff[j][i] != '_')
		{
			if (index == 2)
				printf("bbshell: export: '%s': not a valid identifier\n", ft_substr(buff[j], 0, ft_strchrlen(buff[j], '=')));
			return (-1);
		}
	}
	return(0);
}

int	get_env_from_export(char **buff, int j, int index)
{
	int		i;
	int		checker;

	i = -1;
	checker = 0;
	if (buff[j] && check_if_valid(buff, j, index) == -1)
		return (j + 1);
	while (buff[j] != NULL)
	{
		if (ft_strchr(buff[j], '=') != NULL)
			break ;
		j++;
	}
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
				return (j + 1);
			}
		}
	}
	get_new_env(buff, i, j);
	return (j + 1);
}

int	bi_export2(int j, int i, char **buff, int index)
{
	int	checker;

	checker = 0;
	if (buff[j] && check_if_valid(buff, j, index) == -1)
		return (j);
	if (!buff[j])
		return (j);
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

int	bi_export(char **buff, int index)
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
	while (buff[j++] != NULL)
		j = bi_export2(j, i, buff, index);
	j = 1;
	while (buff[j] != NULL)
		j = get_env_from_export(buff, j, 3);
	return (0);
}

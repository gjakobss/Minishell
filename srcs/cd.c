/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:00:27 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/07 12:17:28 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(char *old, char *new)
{
	int	i;

	i = 0;
	while (g_mini.env[i] && ft_strncmp(g_mini.env[i], "PWD", 3) != 0)
		i++;
	if (g_mini.env[i] != NULL)
		g_mini.env[i] = ft_strjoin("PWD=", new);
	i = 0;
	while (g_mini.env[i] && ft_strncmp(g_mini.env[i], "OLDPWD", 6) != 0)
		i++;
	if (g_mini.env[i] != NULL)
		g_mini.env[i] = ft_strjoin("OLDPWD=", old);
	i = 0;
	while (g_mini.exp[i] && ft_strncmp(g_mini.exp[i], "PWD", 3) != 0)
		i++;
	if (g_mini.exp[i] != NULL)
		g_mini.exp[i] = ft_strjoin("PWD=", new);
	i = 0;
	while (g_mini.exp[i] && ft_strncmp(g_mini.exp[i], "OLDPWD", 6) != 0)
		i++;
	if (g_mini.exp[i] != NULL)
		g_mini.exp[i] = ft_strjoin("OLDPWD=", old);
	return (0);
}

static char	*remove_quotes(char *str)
{
	char	**ptr;
	char	c;

	if (str[0] == '\'')
		c = '\'';
	else if (str[0] == '"')
		c = '"';
	else
		return (str);
	ptr = ft_split(str, c);
	return (ptr[0]);
	
}

int	bi_cd(char *str)
{
	char	new_pwd[1024];
	char	*old_pwd;
	char	*arg;
	int		ret;

	arg = remove_quotes(str);
	old_pwd = getenv("PWD");
	if ((!arg) || (arg[0] == '~' && arg[1] == '\0'))
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(arg);
	if (ret == -1)
	{
		printf("Error changing directory\n");
		return (1);
	}
	getcwd(new_pwd, 1024);
	update_pwd(old_pwd, new_pwd);
	return (0);
}

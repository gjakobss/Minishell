/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:00:27 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/07 14:04:10 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(char *old, char *new)
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

char	*get_env(char *str)
{
	int i;
	int len;
	int	blen;

	len = ft_strlen(str);
	i = -1;
	while (g_mini.env[++i])
	{
		if (ft_strncmp(g_mini.env[i], str, len) == 0)
			break;
	}
	blen = ft_strlen(g_mini.env[i])- len;
	return (ft_substr(g_mini.env[i], len + 1, blen));
}

int	bi_cd(int c, char *str, int index)
{
	char	new_pwd[1024];
	char	old_pwd[1024];
	char	*arg;
	int		ret;

	arg = remove_quotes(str);
	getcwd(old_pwd, 1024);
	if ((!arg) || (arg[0] == '~' && arg[1] == '\0') || g_mini.cmd[c].op == 3)
		ret = chdir(get_env("HOME"));
	if ((arg[0] == '-' && arg[1] == '\0'))
	{
		if (index == 1)
			printf("%s\n", get_env("OLDPWD"));
		ret = chdir(get_env("OLDPWD"));
	}
	else
		ret = chdir(arg);
	if (ret == -1)
	{
		if (index == 1)
			printf("Error changing directory\n");
		return (1);
	}
	if (index == 2)
	{
		getcwd(new_pwd, 1024);
		update_pwd(old_pwd, new_pwd);
	}
	return (0);
}

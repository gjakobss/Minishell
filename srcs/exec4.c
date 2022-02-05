/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:26:23 by gjakobss          #+#    #+#             */
/*   Updated: 2022/02/05 16:26:24 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_one2(int c, int j, int i)
{
	int	status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
	{
		if (g_mini.pid == 0 && j == -1)
			exit(127);
		if (g_mini.pid == 0 && is_builtin(c) != 0)
			exit(exec_one_bi(c, 1));
		if (g_mini.pid == 0 && j == 0)
			execve(ft_str3join(g_mini.bin_paths[i], "/", \
			g_mini.cmd[c].command[0]), g_mini.cmd[c].command, g_mini.env);
		else if (g_mini.pid == 0 && j == 1)
			execve(g_mini.cmd[c].command[0], g_mini.cmd[c].command, g_mini.env);
	}
	if (is_builtin(c) == 2)
		exec_one_bi(c, 2);
	waitpid(g_mini.pid, &status, 0);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	return (0);
}

int	get_j(int i, int c)
{
	int	j;

	while (g_mini.bin_paths[++i] != NULL)
	{
		if (g_mini.cmd[c].command[0][0] == '/'
			|| g_mini.cmd[c].command[0][0] == '.')
			j = access(g_mini.cmd[c].command[0], F_OK);
		if (j == 0)
		{
			j = 1;
			break ;
		}
		if (g_mini.cmd[c].command[0][0] == '/'
			&& g_mini.cmd[c].command[0][0] != '.')
			j = access(g_mini.cmd[c].command[0], F_OK);
		else if (g_mini.cmd[c].command[0][0] != '/')
			j = access(ft_str3join(g_mini.bin_paths[i], "/",
						g_mini.cmd[c].command[0]), F_OK);
		if (j == 0)
			break ;
	}
	return (j);
}

int	get_i(int i, int c)
{
	int	j;

	while (g_mini.bin_paths[++i] != NULL)
	{
		if (g_mini.cmd[c].command[0][0] == '/'
			|| g_mini.cmd[c].command[0][0] == '.')
			j = access(g_mini.cmd[c].command[0], F_OK);
		if (j == 0)
		{
			j = 1;
			break ;
		}
		if (g_mini.cmd[c].command[0][0] == '/'
			&& g_mini.cmd[c].command[0][0] != '.')
			j = access(g_mini.cmd[c].command[0], F_OK);
		else if (g_mini.cmd[c].command[0][0] != '/')
			j = access(ft_str3join(g_mini.bin_paths[i], "/",
						g_mini.cmd[c].command[0]), F_OK);
		if (j == 0)
			break ;
	}
	return (i);
}

int	exec_com2(int c, int i)
{
	int	j;

	i = get_i(-1, c);
	j = get_j(-1, c);
	if ((j == -1 && is_builtin(0) == 0)
		|| ft_strcmp(g_mini.cmd[c].command[0], "exit") == 0)
	{
		if (ft_strcmp(g_mini.cmd[c].command[0], "exit") == 0)
			return (-2);
		printf("bbshell: command not found: %s\n", g_mini.cmd[c].command[0]);
		if (g_mini.cmd[c].op == 3)
			return (0);
		return (-1);
	}
	return (i);
}

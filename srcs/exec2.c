/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:47:34 by gjakobss          #+#    #+#             */
/*   Updated: 2021/12/18 18:47:39 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one2(int c, int j, int i)
{
	int	status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
	{
		if (g_mini.pid == 0 && j == -1)
			exit(127);
		if (g_mini.pid == 0 && is_builtin(0) != 0)
			exit(exec_one_bi(0, 1));
		if (g_mini.pid == 0 && j == 0)
			execve(ft_str3join(g_mini.bin_paths[i], "/", \
			g_mini.cmd[c].command[0]), g_mini.cmd[c].command, g_mini.env);
		else if (g_mini.pid == 0 && j == 1)
			execve(g_mini.cmd[c].command[0], g_mini.cmd[c].command, g_mini.env);
	}
	if (is_builtin(0) == 2)
		exec_one_bi(0, 2);
	waitpid(g_mini.pid, &status, 0);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	return (0);
}

int	exec_com2(int c, int i)
{
	int	j;

	i = 0;
	while (g_mini.bin_paths[i] != NULL)
	{
		if (g_mini.cmd[c].command[0][0] == '/')
			j = access(g_mini.cmd[c].command[0], F_OK);
		else if (g_mini.cmd[c].command[0][0] != '/')
			j = access(ft_str3join(g_mini.bin_paths[i], "/",
						g_mini.cmd[c].command[0]), F_OK);
		if (j == 0)
			break ;
		i++;
	}
	if ((j == -1 && is_builtin(0) == 0) || ft_strcmp(g_mini.cmd[c].command[0], "exit") == 0)
	{
		if (ft_strcmp(g_mini.cmd[c].command[0], "exit") == 0)
			return (-2);
		printf("bbshell: command not found: %s\n", g_mini.cmd[c].command[0]);
		return (-1);
	}
	return (i);
}

int	divergent(int c, int index, int id)
{
	if (id == 0)
	{
		if (g_mini.cmd[c - 1].op == 3)
			return (0);
		if (g_mini.cmd[c - 1].op == 5)
		{
			g_mini.cmd[c - 1].op = 3;
			return (wait_input(c, index));
		}
		return (exec_com_mid(c, index));
	}
	if (g_mini.cmd[c - 1].op == 2)
		return (send_output(c, index, 0));
	if (g_mini.cmd[c - 1].op == 4)
		return (append_output(c, index, 0));
	return (exec_last_com(c, index));
}

int	one_time(int c, int index)
{
	if (g_mini.cmd[c].op == 5 && g_mini.num_cmds == 2)
	{
		wait_input(c, index);
		g_mini.cmd[c].op = 6;
	}
	if (g_mini.cmd[c].op == 3 && g_mini.num_cmds == 2)
	{
		send_input(c, index);
		g_mini.cmd[c].op = 6;
	}
	if (g_mini.cmd[c].op == 6)
		exec_one(c);
	return (0);
}

int	multi_exec(int c, int index, int i)
{
	g_mini.pipefd = malloc(sizeof(int *) * (g_mini.pipes * 2));
	while (i < g_mini.pipes * 2)
	{
		g_mini.pipefd[i] = malloc(sizeof(int) * 2);
		pipe(g_mini.pipefd[i++]);
	}
	if (g_mini.cmd[c].op == 5)
	{
		wait_input(c, index);
		g_mini.cmd[c].op = 3;
	}
	if (g_mini.cmd[c].op == 3)
		send_input(c, index);
	if (exec_com_one(c, index) == -1)
		return (-1);
	index++;
	c++;
	while (g_mini.cmd[c].op != 6)
		if (divergent(c++, index++, 0) == -1)
			return (-1);
	return (divergent(c, index, 1));
}

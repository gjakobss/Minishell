/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:45 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/15 13:02:20 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one(void)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
	while (g_mini.bin_paths[++i] != NULL)
	{
		if (g_mini.cmd->command[0][0] == '/')
			j = access(g_mini.cmd->command[0], F_OK);
		if (j == 0)
		{
			j = 1;
			break ;
		}
		else if (g_mini.cmd->command[0][0] != '/')
			j = access(ft_str3join(g_mini.bin_paths[i], "/",
						g_mini.cmd->command[0]), F_OK);
		if (j == 0)
			break ;
	}
	if (j == -1 && is_builtin(0) == 0)
		printf("bbshell: command not found: %s\n", g_mini.cmd->command[0]);
	if (is_builtin(0) != 0)
		j = 1;
	return (exec_one2(j, i));
}

int	exec_com_one(int c, int index)
{
	int	i;
	int	status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
	{
		i = exec_com2(c, 0);
		if (i == -1)
			exit(127);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index][1], 1);
		if (is_builtin(c) == 1)
			exit(exec_one_bi(c));
		execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
			g_mini.cmd[c].command, g_mini.env);
	}
	waitpid(g_mini.pid, &status, 0);
	close (g_mini.pipefd[index][1]);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	if (g_mini.status != 0)
		return (-1);
	return (0);
}

int	exec_com_mid(int c, int index)
{
	int	i;
	int	status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
	{
		i = exec_com2(c, 0);
		if (i == -1)
			exit(127);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		dup2(g_mini.pipefd[index][1], 1);
		if (is_builtin(c) == 1)
			exit(exec_one_bi(c));
		execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
			g_mini.cmd[c].command, g_mini.env);
	}
	waitpid(g_mini.pid, &status, 0);
	close (g_mini.pipefd[index][1]);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	if (g_mini.status != 0)
		return (-1);
	return (index);
}

int	exec_last_com(int c, int index)
{
	int	i;
	int	status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
	{
		i = exec_com2(c, 0);
		if (i == -1)
			exit(127);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		if (is_builtin(c) == 1)
			exit(exec_one_bi(c) * 256);
		execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
			g_mini.cmd[c].command, g_mini.env);
	}
	waitpid(g_mini.pid, &status, 0);
	close (g_mini.pipefd[index][1]);
	close(g_mini.pipefd[index][0]);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	return (0);
}

int	send_to_exec(void)
{
	int	c;
	int	index;

	c = 0;
	index = 0;
	g_mini.child = 1;
	if (g_mini.cmd[c].op == 6 || g_mini.num_cmds == 2)
		one_time(c, index);
	if (g_mini.cmd[0].op != 6)
		if (multi_exec(c, index, 0) == -1)
			return (-1);
	g_mini.child = 0;
	return (0);
}

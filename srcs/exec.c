/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:45 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/27 11:58:19 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_one(void)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (g_mini.bin_paths[i] != NULL)
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
		i++;
	}
	if (j == -1)
		printf("bbshell: command not found: %s\n", g_mini.cmd->command[0]);
	exec_one2(j, i);
}

int	exec_com_one(int c, int index)
{
	int	i;
	int	id;
	int status;

	id = fork();
	if (id == 0)
	{
		i = exec_com2(c, 0, 2);
		if (i == -1)
			return (-1);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index][1], 1);
		if (is_builtin(c) == 1)
		{
			g_mini.status = exec_one_bi(c) * 256;
			exit(g_mini.status);
		}
		execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
			g_mini.cmd[c].command, g_mini.env);
	}
	waitpid(id, &status, 0); //WIFEXITED WEXITSTATUS
	close (g_mini.pipefd[index][1]);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	return (0);
}

int	exec_com_mid(int c, int index)
{
	int	id;
	int	i;

	id = fork();
	if (id == 0)
	{
		i = exec_com2(c, 0, 2);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		dup2(g_mini.pipefd[index][1], 1);
		if (is_builtin(c) == 1)
		{
			g_mini.status = exec_one_bi(c) * 256;
			exit(g_mini.status);
		}
		execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
			g_mini.cmd[c].command, g_mini.env);
	}
	wait(NULL);
	close(g_mini.pipefd[index][1]);
	return (index);
}

int	exec_last_com(int c, int index)
{
	int	id;
	int	i;

	id = fork();
	if (id == 0)
	{
		i = exec_com2(c, 0, g_mini.cmd[c - 1].op);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		if (is_builtin(c) == 1)
		{
			g_mini.status = exec_one_bi(c) * 256;
			exit(g_mini.status);
		}
		execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
			g_mini.cmd[c].command, g_mini.env);
	}
	else
	{
		wait(NULL);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
	}
	return (0);
}

int	send_to_exec(void)
{
	int	c;
	int	index;

	c = 0;
	index = 0;
	if (g_mini.cmd[c].op == 6 || g_mini.num_cmds == 2)
		one_time(c, index);
	if (g_mini.cmd[0].op != 6)
		multi_exec(c, index, 0);
	return (0);
}

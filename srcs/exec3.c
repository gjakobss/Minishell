/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:15:44 by gjakobss          #+#    #+#             */
/*   Updated: 2022/02/03 16:15:46 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_com_mid2(int c, int index, int i, int x)
{
	char	**sub;

	i = exec_com2(c, 0);
	if (i == -1)
		exit(127);
	if (i == -2)
		exit(128);
	close(g_mini.pipefd[index][0]);
	dup2(g_mini.pipefd[index - 1][0], 0);
	if (g_mini.cmd[c].op != 3)
		dup2(g_mini.pipefd[index][1], 1);
	else
		close(g_mini.pipefd[index][1]);
	if (is_builtin(c) == 1)
		exit(exec_one_bi(c, 2));
	if (g_mini.cmd[c].op == 2 || g_mini.cmd[c].op == 4)
	{
		sub = get_sub(c, x, x + 1, -1);
		execve(ft_str3join(g_mini.bin_paths[i], "/",
				g_mini.cmd[c].command[0]), sub, g_mini.env);
	}
	execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
		g_mini.cmd[c].command, g_mini.env);
}

int	exec_com_mid(int c, int index)
{
	int		status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
		exec_com_mid2(c, index, 0, c);
	waitpid(g_mini.pid, &status, 0);
	close (g_mini.pipefd[index][1]);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	if (g_mini.status == 128)
		return (index);
	if (g_mini.status != 0 && g_mini.cmd[c].op != 3)
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
		if (i == -1 || i == -2)
			exit(127);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		if (is_builtin(c) == 1)
			exit(exec_one_bi(c, 2) * 256);
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
	int	cat;
	int	index;

	c = 0;
	index = 0;
	g_mini.child = 1;
	cat = 0;
	if (ft_strcmp(g_mini.cmd[c].command[0], "cat") == 0
		&& !g_mini.cmd[c].command[1] && g_mini.cmd[c].op == 1)
	{
		c = cat_fix(c);
		cat = c;
	}
	if (g_mini.cmd[c].op == 6 || g_mini.num_cmds <= 2)
		one_time(c, index);
	if (g_mini.cmd[c].op != 6)
	{
		if (multi_exec(c, index, 0) == -1)
			return (-1);
	}
	if (cat > 0)
		exec_cat(0, cat);
	g_mini.child = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:45 by malmeida          #+#    #+#             */
/*   Updated: 2022/01/07 14:08:54 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_one(int c)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
	while (g_mini.bin_paths[++i] != NULL)
	{
		if (g_mini.cmd[c].command[0][0] == '/')
			j = access(g_mini.cmd[c].command[0], F_OK);
		if (j == 0)
		{
			j = 1;
			break ;
		}
		else if (g_mini.cmd[c].command[0][0] != '/')
			j = access(ft_str3join(g_mini.bin_paths[i], "/",
						g_mini.cmd[c].command[0]), F_OK);
		if (j == 0)
			break ;
	}
	if (j == -1 && is_builtin(c) == 0 && ft_strcmp(g_mini.cmd->command[0], "exit") != 0)
		printf("bbshell: command not found: %s\n", g_mini.cmd->command[0]);
	if (is_builtin(c) != 0)
		j = 1;
	return (exec_one2(c, j, i));
}

char	**get_sub(int c, int x)
{
	int		len;
	char	**new;
	int		i;
	int		j;
	int temp;

	temp = x + 1;
	len = ft_arraylen(g_mini.cmd[c].command);
	while (g_mini.cmd[x].op == 2 || g_mini.cmd[x].op == 4)
	{
		len += ft_arraylen(g_mini.cmd[x].command);
		x++;
	}
	new = malloc(sizeof(char *) * (len + 1));
	i = -1;
	j = 0;
	while (g_mini.cmd[c].command[++i])
	{
		new[j] = ft_strdup(g_mini.cmd[c].command[i]);
		j++;
	}
	while (temp <= x)
	{
		i = 0;
		while (g_mini.cmd[temp].command[++i])
		{
			new[j] = ft_strdup(g_mini.cmd[temp].command[i]);
			j++;
		}
		temp++;
	}
	new[j] = NULL;
	return (new);
}

int	exec_com_one(int c, int index)
{
	int	i;
	int x;
	char	**sub;
	int	status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
	{
		i = exec_com2(c, 0);
		if (i == -1)
			exit(127);
		if (i == -2)
			exit(128);
		close(g_mini.pipefd[index][0]);
		if (g_mini.cmd[c].op != 3)
			dup2(g_mini.pipefd[index][1], 1);
		else
			close(g_mini.pipefd[index][1]);
		if (is_builtin(c) == 1)
			exit(exec_one_bi(c, 2));
		if (g_mini.cmd[c].op == 2 || g_mini.cmd[c].op == 4)
		{
			x = c;
			sub = get_sub(c, x);
			execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
				sub, g_mini.env);
		}
		if (g_mini.cmd[c].op != 3)
			execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
				g_mini.cmd[c].command, g_mini.env);
		else
			exit(0);
	}
	waitpid(g_mini.pid, &status, 0);
	close (g_mini.pipefd[index][1]);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	if (g_mini.status != 0 && g_mini.status != 128  && g_mini.cmd[c].op != 3)
		return (-1);
	return (0);
}

int	exec_com_mid(int c, int index)
{
	int	i;
	int x;
	char **sub;
	int	status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
	{
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
			x = c;
			sub = get_sub(c, x);
			execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
				sub, g_mini.env);
		}
		execve(ft_str3join(g_mini.bin_paths[i], "/", g_mini.cmd[c].command[0]),
			g_mini.cmd[c].command, g_mini.env);
	}
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
	if (g_mini.cmd[c].op == 6 ||  g_mini.num_cmds <= 2)
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

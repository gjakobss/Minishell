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

int	exec_one3(int j, char c)
{
	if (j == -1 && is_builtin(c) == 0
		&& ft_strcmp(g_mini.cmd->command[0], "exit") != 0)
		printf("bbshell: command not found: %s\n", g_mini.cmd->command[0]);
	if (is_builtin(c) != 0)
		j = 1;
	return (j);
}

int	exec_one(int c)
{
	int	i;
	int	j;

	i = -1;
	j = 2;
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
		if (g_mini.cmd[c].command[0][0] != '/'
			&& g_mini.cmd[c].command[0][0] != '.')
			j = access(ft_str3join(g_mini.bin_paths[i], "/",
						g_mini.cmd[c].command[0]), F_OK);
		if (j == 0)
			break ;
	}
	j = exec_one3(j, c);
	return (exec_one2(c, j, i));
}

char	**get_sub(int c, int x, int temp, int i)
{
	int		len;
	char	**new;
	int		j;

	len = ft_arraylen(g_mini.cmd[c].command);
	while (g_mini.cmd[x].op == 2 || g_mini.cmd[x].op == 4)
		len += ft_arraylen(g_mini.cmd[x++].command);
	new = malloc(sizeof(char *) * (len + 1));
	j = 0;
	while (g_mini.cmd[c].command[++i])
		new[j++] = ft_strdup(g_mini.cmd[c].command[i]);
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

int	exec_com_one2(int c, int index, int i, int x)
{
	char	**sub;

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
		sub = get_sub(c, x, x + 1, -1);
		execve(ft_str3join(g_mini.bin_paths[i], "/",
				g_mini.cmd[c].command[0]), sub, g_mini.env);
	}
	if (g_mini.cmd[c].op != 3)
		execve(ft_str3join(g_mini.bin_paths[i], "/",
				g_mini.cmd[c].command[0]),
			g_mini.cmd[c].command, g_mini.env);
	exit(0);
}

int	exec_com_one(int c, int index, int i)
{
	int		status;

	g_mini.pid = fork();
	if (g_mini.pid == 0)
		exec_com_one2(c, index, i, c);
	waitpid(g_mini.pid, &status, 0);
	close (g_mini.pipefd[index][1]);
	if (WIFEXITED(status))
		g_mini.status = WEXITSTATUS(status);
	if (g_mini.status != 0 && g_mini.status != 128 && g_mini.cmd[c].op != 3)
		return (-1);
	return (0);
}

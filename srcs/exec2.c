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

int	divergent2(int c, int id, int index)
{
	if (g_mini.cmd[c - 1].op == GREATER)
		return (send_output(c, index, 0));
	if (g_mini.cmd[c - 1].op == DGREATER)
		return (append_output(c, index, 1));
	if (id == 0)
		return (exec_com_mid(c, index));
	return (exec_last_com(c, index));
}

int	divergent(int c, int index, int id, int temp)
{
	if (g_mini.cmd[c - 1].op == SMALLER || g_mini.cmd[c - 1].op == 6)
		return (0);
	if (g_mini.cmd[c].op == DSMALLER)
	{
		wait_input(c, index);
		if (!g_mini.cmd[c].command[1]
			&& !ft_strcmp(g_mini.cmd[c].command[0], "cat"))
			g_mini.cmd[c].op = 7;
		else
			g_mini.cmd[c].op = g_mini.cmd[c].hdop;
	}
	if (g_mini.cmd[c].op == 3)
	{
		while (g_mini.cmd[temp].op == 3)
			temp++;
		if (g_mini.cmd[temp].op == 6)
		{
			send_input(c, index);
			return (one_time(c, index, c));
		}
		return (0);
	}
	return (divergent2(c, id, index));
}

int	one_time(int c, int index, int temp)
{
	while (g_mini.cmd[temp].op == 3)
		temp++;
	if (g_mini.cmd[c].op == 5 && g_mini.num_cmds < 2)
	{
		wait_input(c, index);
		if (!g_mini.cmd[c].command[1]
			&& !ft_strcmp(g_mini.cmd[c].command[0], "cat"))
		{
			g_mini.cmd[c].op = 6;
			return (0);
		}
		g_mini.cmd[c].op = g_mini.cmd[c].hdop;
	}
	if ((g_mini.cmd[c].op == 3 && g_mini.num_cmds == 2)
		|| (g_mini.cmd[c].op == 3 && g_mini.cmd[temp].op == 6))
	{
		send_input(c, index);
		exec_one(c);
		g_mini.cmd[c].op = 6;
		return (0);
	}
	if (g_mini.cmd[c].op == 6)
		exec_one(c);
	return (0);
}

int	multi_exec2(int i, int c, int index, int temp)
{
	while (i < g_mini.pipes * 2)
	{
		g_mini.pipefd[i] = malloc(sizeof(int) * 2);
		pipe(g_mini.pipefd[i++]);
	}
	if (g_mini.cmd[c].op == 5)
	{
		wait_input(c, index);
		if (!g_mini.cmd[c].command[1]
			&& !ft_strcmp(g_mini.cmd[c].command[0], "cat"))
			g_mini.cmd[c].op = 7;
		else
			g_mini.cmd[c].op = g_mini.cmd[c].hdop;
	}
	if (g_mini.cmd[c].op == 3)
	{
		send_input(c, index);
		while (g_mini.cmd[temp].op == 3)
			temp++;
		if (g_mini.cmd[temp].op == 6)
			return (one_time(c, index, c));
		exec_one(c);
	}
	return (1);
}

int	multi_exec(int c, int index, int i)
{
	int	ret;

	g_mini.pipefd = malloc(sizeof(int *) * (g_mini.pipes * 2));
	if (multi_exec2(i, c, index, c) == 0)
		return (0);
	if (g_mini.cmd[c].op != 3 && g_mini.cmd[c].op <= 6)
		if (exec_com_one(c, index, 0) == -1)
			return (-1);
	index++;
	c++;
	while (g_mini.cmd[c].op != 6 && g_mini.cmd[c].hdop != 6)
	{
		ret = divergent(c, index, 0, c);
		c++;
		index++;
		if (ret == -1)
			return (-1);
		else if (ret == -2)
			return (0);
		while ((g_mini.cmd[c].op == 2 && g_mini.cmd[c - 1].op == 2)
			|| (g_mini.cmd[c].op == 4 && g_mini.cmd[c - 1].op == 4))
			c++;
	}
	return (divergent(c, index, 1, c));
}

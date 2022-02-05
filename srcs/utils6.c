/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:20:37 by gjakobss          #+#    #+#             */
/*   Updated: 2022/02/05 18:20:38 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	append_output2(int c, int index, int i)
{
	char	*buff;
	int		fd;

	fd = open(g_mini.cmd[c].command[0],
			O_WRONLY | O_CREAT | O_APPEND, 0777);
	close_pipes(index);
	while (get_next_line(g_mini.pipefd[index - 1][0], &buff) != 0)
	{
		if (i == 0)
			write(fd, "\n", 1);
		write(fd, buff, ft_strlen(buff));
		i = 0;
	}
	if (ft_strcmp(g_mini.cmd[c - 1].command[0], "echo") == 0)
	{
		write(fd, " ", 1);
		while (g_mini.cmd[c].command[++i])
			write(fd, ft_strjoin(g_mini.cmd[c].command[i], " "),
				ft_strlen(g_mini.cmd[c].command[i]) + 1);
	}
	write(fd, "\n", 1);
	exit(0);
}

#include "minishell.h"

int	send_output(int c, int index, int i)
{
	int		fd;
	int		id;
	char	*buff;

	while (g_mini.cmd[c].command[++i])
		printf("%s: %s: No such file or directory\n",
			g_mini.cmd[c - 1].command[0], g_mini.cmd[c].command[i]);
	if (g_mini.cmd[c].command[1])
	{
		fd = open(g_mini.cmd[c].command[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		return (0);
	}
	id = fork();
	if (id == 0)
	{
		fd = open(g_mini.cmd[c].command[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		while (get_next_line(g_mini.pipefd[index - 1][0], &buff) != 0)
			write(fd, buff, ft_strlen(buff));
		exit(0);
	}
	wait(NULL);
	close(g_mini.pipefd[index][1]);
	close(g_mini.pipefd[index][0]);
	return (0);
}

int	append_output(int c, int index, int i)
{
	int		fd;
	int		id;
	char	*buff;

	(void)i;
//	while (g_mini.cmd[c].command[++i])
//		printf("%s: %s: No such file or directory\n",
//			g_mini.cmd[c - 1].command[0], g_mini.cmd[c].command[i]);
//	if (g_mini.cmd[c].command[1])
//	{
//		fd = open(g_mini.cmd[c].command[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
//		return (0);
//	}
	id = fork();
	if (id == 0)
	{
		fd = open(g_mini.cmd[c].command[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		while (get_next_line(g_mini.pipefd[index - 1][0], &buff) != 0)
			write(fd, buff, ft_strlen(buff));
		exit(0);
	}
	wait(NULL);
	close(g_mini.pipefd[index][1]);
	close(g_mini.pipefd[index][0]);
	return (0);
}

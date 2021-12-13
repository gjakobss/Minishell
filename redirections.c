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

	id = fork();
	if (id == 0)
	{
		fd = open(g_mini.cmd[c].command[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		if (g_mini.cmd[c + 1].command)
		exit(0);
		while (get_next_line(g_mini.pipefd[index - 1][0], &buff) != 0)
			write(fd, buff, ft_strlen(buff));
		while (g_mini.cmd[c].command[++i])
			write(fd, ft_strjoin(g_mini.cmd[c].command[i], "\n"), ft_strlen(g_mini.cmd[c].command[i]) + 1);
		exit(0);
	}
	wait(NULL);
	close(g_mini.pipefd[index][1]);
	close(g_mini.pipefd[index][0]);
	return (0);
}

int	send_input(int c, int index)
{
	int	i;
	char *temp;

	(void)index;
	i = 0;
	if (!g_mini.cmd[c].command[1])
		while (g_mini.cmd[c + 1].command[i])
			i++;
	else
		return (0);
	temp = ft_strdup(g_mini.cmd[c].command[0]);
	free(g_mini.cmd[c].command[0]);
	free(g_mini.cmd[c].command);
	g_mini.cmd[c].command = malloc(sizeof(char *) * 3);
	g_mini.cmd[c].command[0] = ft_strdup(temp);
	g_mini.cmd[c].command[1] = ft_strdup(g_mini.cmd[c + 1].command[i - 1]);
	g_mini.cmd[c].command[2] = NULL;
	return (0);
}

int	wait_input(int c, int index)
{
	char *line;

	(void)index;
	line = readline("heredoc> ");
	while (ft_strcmp(line, g_mini.cmd[c + 1].command[0]) != 0)
		line = readline("heredoc> ");
	return (0);
}

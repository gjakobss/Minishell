#include "minishell.h"

char	**init_env(char **o_env)
{
	int i;
	int j;
	char	**env;

	i = 0;

	while (o_env[i] != NULL)
	{
		i++;
	}
	env = malloc(sizeof(char*) * i + 1);
	i = 0;
	while (o_env[i] != NULL)
	{
		env[i] = o_env[i];
		i++;
	}
	j = 0;
	return (env);
}

int	get_bin_path(void)
{
	int i;

	i = 0;
//	usar o getenv("PATH")
	while (g_mini.env[i] != NULL)
	{
		if (g_mini.env[i][0] == 'P' && g_mini.env[i][1] == 'A')
			break;
		i++;
	}
	g_mini.bin_paths = ft_split(g_mini.env[i] + 5, ':');
	return (0);
}

void	exec_one_bi(int x)
{
	char	*str;
	str = g_mini.cmd[x].command[0];
	if (!ft_strcmp(str, "cd"))
		bi_cd(g_mini.cmd[x].command[1]);
	if (!ft_strcmp(str, "pwd"))
		bi_pwd();
	if (!ft_strcmp(str, "env"))
		bi_env();
	if (!ft_strcmp(str, "echo"))
		bi_echo(g_mini.cmd[x].command);
}

int	is_builtin(int x)
{
	char	*str;

	str = g_mini.cmd[x].command[0];
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "pwd") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset") || !ft_strcmp(str, "cd"))
		return (1);
	return (0);

}

void exec_one(void)
{
	int i;
	int j;
	int id;

	i = 0;
	j = 0;
	while(g_mini.bin_paths[i] != NULL)
	{
			j = access(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd->command[0]), F_OK);
			if (j == 0)
				break;
			i++;
	}
		if (j == -1)
			printf("bbshell: command not found: %s\n", g_mini.cmd->command[0]);
		id = fork();
		if (id == 0 && j == 0)
			execve(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd->command[0]), g_mini.cmd->command, 0);
		else
			wait(NULL);
}

void	exec_com_one(int c, int index)
{
	int i;
	int j;
	int id;

	i = 0;
	id = fork();
		if (id == 0)
		{
			while (g_mini.bin_paths[i] != NULL)
			{
				j = access(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd[c].command[0]), F_OK);
				if (j == 0)
					break ;
				i++;
			}
			if (j == -1 && is_builtin(c) == 0)
				printf("command not found: %s\n", g_mini.cmd[c].command[0]);
			close(g_mini.pipefd[index][0]);
			dup2(g_mini.pipefd[index][1], 1);
			if (is_builtin(c) == 1)
			{
				exec_one_bi(c);
				exit(0);
			}
			else
				execve(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd[c].command[0]), g_mini.cmd[c].command, 0);
		}
		else
		{
			wait(NULL);
			close (g_mini.pipefd[index][1]);
		}
}

int	exec_com_mid(int c, int index)
{
	int id;
	int i;
	int j;

	i = 0;
	id = fork();
	if	(id == 0)
	{

		while (g_mini.bin_paths[i] != NULL)
		{
			j = access(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd[c].command[0]), F_OK);
			if (j == 0)
				break ;
			i++;
		}
		if (j == -1 && is_builtin(0) == 1)
			j = 0;
		else if (j == -1 && is_builtin(0) == 0)
			printf("command not found: %s\n", g_mini.cmd[c].command[0]);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		dup2(g_mini.pipefd[index][1], 1);
		if (is_builtin(c) == 1)
			{
				exec_one_bi(c);
				exit(0);
			}
		else
		execve(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd[c].command[0]), g_mini.cmd[c].command, 0);
	}
	wait(NULL);
	close(g_mini.pipefd[index][1]);
	return (index);
}

void	exec_last_com(int c, int index)
{
	int id;
	int i;
	int j;

	i = 0;
	id = fork();
	if (id == 0)
	{
		i = 0;
		while (g_mini.bin_paths[i] != NULL)
		{
			j = access(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd[c].command[0]), F_OK);
			if (j == 0)
				break ;
			i++;
		}
		if (j == -1)
			printf("command not found: %s\n", g_mini.cmd[c].command[0]);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		if (is_builtin(c) == 1)
			{
				exec_one_bi(c);
				exit(0);
			}
		else
		execve(ft_strjoin(g_mini.bin_paths[i], "/" , g_mini.cmd[c].command[0]), g_mini.cmd[c].command, 0);
	}
	else
	{
		wait(NULL);
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
	}
}


int	send_to_exec(void)
{
	int i;
	int c;
	int	index;

	i = 0;
	c = 0;
	index = 0;
	if (g_mini.pipes == 0 && is_builtin(0) == 1)
		exec_one_bi(0);
	else if (g_mini.pipes == 0 && is_builtin(0) == 0)
		exec_one();
	else
	{
		g_mini.pipefd = malloc(sizeof(int *) * g_mini.pipes);
		while (i < g_mini.pipes)
		{
			g_mini.pipefd[i] = malloc(sizeof(int) * 2);
			pipe(g_mini.pipefd[i++]);
		}
		exec_com_one(c, index);
		index++;
		c++;
		g_mini.pipes /= 2;
		while (--g_mini.pipes > 0)
		{
			exec_com_mid(c, index);
			c++;
			index++;
		}
		exec_last_com(c, index);
	}
	return (0);
}

void	init_g()
{
	g_mini.pipes = 0;

}

int main(int argc, char **argv, char **o_env)
{
	char *line;

	(void)argc;
	(void)argv;

	g_mini.env = init_env(o_env);
	while (1)
	{
		init_g();
		line = readline("BBShell >$ ");
		if (!line)
			continue;
		if (ft_strcmp(line, "exit") == 0)
			break ;
		g_mini.cmd = parser(line);
		if (g_mini.cmd == NULL)
			continue ;
		get_bin_path();
		send_to_exec();
		//need to update env with getenv();
	}
	free(g_mini.env);
//	free(g_mini.cmd->command);
	free(g_mini.cmd);
}






//Tentativa bem sucedida de fazer dois comandos (SÓ 2).

/*	else
	{
		pipe(g_mini.pipefd);
		id = fork();
		if (id == 0)
		{
			while (g_mini.bin_paths[i] != NULL)
			{
				j = access(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd->command[0]), F_OK);
				if (j == 0)
					break ;
				i++;
			}
			if (j == -1)
				printf("NO PATHS AVAILABLE (built-ins not included)\n");
			close(g_mini.pipefd[0]);
			dup2(g_mini.pipefd[1], 1);
			execve(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd->command[0]), g_mini.cmd->command, 0);
		}
		else
		{
			id = fork();
			if (id == 0)
			{
				i = 0;
				while (g_mini.bin_paths[i] != NULL)
				{
					j = access(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.cmd[1].command[0]), F_OK);
					if (j == 0)
						break ;
					i++;
				}
				if (j == -1)
					printf("NO PATHS AVAILABLE (built-ins not included)\n");
				close(g_mini.pipefd[1]);
				dup2(g_mini.pipefd[0], 0);
				execve(ft_strjoin(g_mini.bin_paths[i], "/" , g_mini.cmd[1].command[0]), g_mini.cmd[1].command, 0);
			}
			else
			{
				close(g_mini.pipefd[0]);
				close(g_mini.pipefd[1]);
				wait(NULL);
			}
			wait(NULL);
		}
	}
	return (0);*/

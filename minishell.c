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

/*int	parse_commands(void)
{
	int j;
	int i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (g_mini.commands[i] != NULL)
	{
		j = 0;
		while(g_mini.commands[i][j] != '\0')
		{
			if (g_mini.commands[i][j] == '\'' && d_quotes % 2 == 0)
				s_quotes += 1;
			else if (g_mini.commands[i][j] == '\"' && s_quotes % 2 == 0)
				d_quotes += 1;
			if (g_mini.commands[i][j] == '|' && (d_quotes % 2 == 0 && s_quotes % 2 == 0))
			{
				g_mini.pipes += 1;
			}
			j++;
		}
		i++;
	}
	if (g_mini.pipes)
		printf("pi-pi-piiiiipe\n");
	if ((d_quotes % 2 != 0) || (s_quotes % 2 != 0))
	{
		printf("Unclosed quotation mark\n");
		return (-1);
	}
	return (0);
}*/

int	get_bin_path(void)
{
	int i;

	i = 0;
	while (g_mini.env[i] != NULL)
	{
		if (g_mini.env[i][0] == 'P' && g_mini.env[i][1] == 'A')
			break;
		i++;
	}
	g_mini.bin_paths = ft_split(g_mini.env[i] + 5, ':');
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
			printf("NO PATHS AVAILABLE (built-ins not included)\n");
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
			if (j == -1)
				printf("NO PATHS AVAILABLE (built-ins not included)\n");
			close(g_mini.pipefd[index][0]);
			dup2(g_mini.pipefd[index][1], 1);
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
		if (j == -1)
			printf("NO PATHS AVAILABLE (built-ins not included)\n");
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		dup2(g_mini.pipefd[index][1], 1);
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
			printf("NO PATHS AVAILABLE (built-ins not included)\n");
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		dup2(g_mini.pipefd[index - 1][0], 0);
		execve(ft_strjoin(g_mini.bin_paths[i], "/" , g_mini.cmd[c].command[0]), g_mini.cmd[c].command, 0);
	}
	else
	{
		close(g_mini.pipefd[index][1]);
		close(g_mini.pipefd[index][0]);
		wait(NULL);
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
	if (g_mini.pipes == 0)
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
		if (ft_strlen(line) == 0)
			continue ;
		if (ft_strcmp(line, "exit") == 0)
			break ;
		g_mini.cmd = parser(line);
		if (g_mini.cmd == NULL)
			continue ;
		get_bin_path();
		send_to_exec();
	}
	free(g_mini.env);
//	free(g_mini.cmd->command);
//	free(g_mini.cmd);
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

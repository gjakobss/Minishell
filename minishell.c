#include "minishell.h"

typedef struct	s_mini
{
	char	**bin_paths;
	char	**env;
	char	**commands;
	int		pipes;
	int		quotes;
	int		pipe[2];

}				t_mini;

t_mini	g_mini;

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

int	parse_commands(void)
{
	int j;
	int i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	g_mini.pipes = 0;
	while (g_mini.commands[i] != NULL)
	{
		j = 0;
		while(g_mini.commands[i][j] != '\0')
		{
			if (g_mini.commands[i][j] == '\'')
				s_quotes += 1;
			else if (g_mini.commands[i][j] == '\"')
				d_quotes += 1;
			if (g_mini.commands[i][j] == '|')
				g_mini.pipes += 1;
			j++;
		}
		i++;
	}
	if (g_mini.pipes)
		printf("pi-pi-piiiiipe\n");
	if ((d_quotes % 2 != 0) || (s_quotes % 2 != 0))
	{
		printf("Wrong quotes biiiitch\n");
		return (-1);
	}
	return (0);
}

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

int	executor(void)
{
	char *path;
	int i;
	int j;
	int id;

	i = 0;
	if (g_mini.pipes == 0)
	{
		while(g_mini.bin_paths[i] != NULL)
		{
			j = access(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.commands[0]), F_OK);
			if (j == 0)
				break;
			i++;
		}
		if (j == -1)
			printf("NO PATHS AVAILABLE CRALHES\n");
		id = fork();
		if (id == 0 && j == 0)
		{
			execve(ft_strjoin(g_mini.bin_paths[i], "/" ,g_mini.commands[0]), g_mini.commands, 0);
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}

int main(int argc, char **argv, char **o_env)
{
	char *line;

	(void)argc;
	(void)argv;
//	env
	g_mini.env = init_env(o_env);
//	line = NULL;
	while (ft_strcmp(line, "exit") != 0)
	{
//	prompt
//		put_prompt();
		line = readline("BBShell >$ ");
		if (line != NULL)
			g_mini.commands = ft_split(line, ' ');
//	parse
		parse_commands();
		get_bin_path();
//	exec
		executor();
	}


//	embelezar
	free(g_mini.env);
	free(g_mini.commands);
}

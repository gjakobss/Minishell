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

void	put_prompt(void)
{
	write(1, "BBShell >$ ", 11);
}

void	parse_commands(char **comands)
{

}

int main(int argc, char **argv, char **o_env)
{
	char	**env;
	char	*line;
	char	**commands;

	(void)argc;
	(void)argv;
//	env
	env = init_env(o_env);
//	line = NULL;
	while (ft_strcmp(line, "exit") != 0)
	{
//	prompt
		put_prompt();
		line = readline(NULL);
		if (line != NULL)
			commands = ft_split(line, ' ');
//	parse
		parse_commands(commands);
//	exec
	}




//	embelezar
	free(env);
	free(commands);
}

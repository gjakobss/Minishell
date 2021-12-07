#include "minishell.h"

char	**init_env(char **o_env)
{
	int		i;
	char	**env;

	i = 0;
	while (o_env[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (o_env[i] != NULL)
	{
		env[i] = o_env[i];
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	init_g(void)
{
	g_mini.pipes = 0;
	g_mini.s_quotes = 0;
	g_mini.d_quotes = 0;
	g_mini.semi_col = 0;
	g_mini.dollar = 0;
}

int	main(int argc, char **argv, char **o_env)
{
	char	*line;

	(void)argc;
	(void)argv;

	g_mini.env = init_env(o_env);
	g_mini.exp = exp_organizer(o_env, NULL);
	while (1)
	{
		init_g();
		line = readline("BBShell >$ ");
		if (!line || line[0] == '\0')
			continue ;
		else
		{
			if (ft_strcmp(line, "exit") == 0)
				break ;
			if (arg_validation(line))
				continue ;
			g_mini.cmd = parser(line);
			add_history(line);
			if (get_bin_path() == -1)
			{
				printf("bbshell: command not found: %s\n",  g_mini.cmd[0].command[0]);
				continue;
			}
			if (send_to_exec() == -1)
				continue;
		}
		free(line);
		//need to update env with getenv();
	}
	free(g_mini.env);
	free(g_mini.cmd);
}

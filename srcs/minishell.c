/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:26:09 by gjakobss          #+#    #+#             */
/*   Updated: 2021/12/20 19:26:11 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	g_mini.status = 1;
}

int	take_care(char *line)
{
	if (arg_validation(line))
		return (-1);
	add_history(line);
	g_mini.cmd = parser(line);
	if (get_bin_path() == -1)
	{
		printf("bbshell: command not found: %s\n", g_mini.cmd[0].command[0]);
		return (-1);
	}
	if (send_to_exec() == -1)
		return (-1);
	return (0);
}

int	garbage_collector(void)
{
	free(g_mini.env);
	free(g_mini.cmd);
	free(g_mini.pipefd);
	return (0);
}

int	main(int argc, char **argv, char **o_env)
{
	char	*line;

	(void)argc;
	(void)argv;
	init_g();
	g_mini.env = init_env(o_env);
	g_mini.exp = exp_organizer(o_env, NULL, 0, 0);
	activate_signals();
	while (1)
	{
		line = readline("BBShell >$ ");
		if (!line || line[0] == '\0')
			continue ;
		else
		{
			if (ft_strcmp(line, "exit") == 0)
				exit(0);
			if (take_care(line) == -1)
				continue ;
			printf("%d\n", g_mini.status);
		}
		free(line);
	}
	return (garbage_collector());
}

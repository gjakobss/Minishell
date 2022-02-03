/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:26:09 by gjakobss          #+#    #+#             */
/*   Updated: 2022/02/02 16:21:37 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_mini.t.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, &g_mini.t);
	return (0);
}

int	ft_exitoi(char *s)
{
	int			i;
	int			minus;
	long long	nbr;

	i = -1;
	nbr = 0;
	while (s[++i])
	{
		if (s[i] == '-')
			minus = 1;
		if ((ft_isalnum((int)s[i]) == 1 && ft_isalpha((int)s[i]) == 1)
			|| ft_isalnum((int)s[i]) == 0)
			return (257);
	}
	i = -1;
	if (minus)
		i = 0;
	while (s[++i])
		nbr = nbr * 10 + (s[i] - 48);
	if (minus)
		nbr *= -1;
	if (nbr == 257)
		return (1);
	return (nbr);
}

int	ft_exit(char *line)
{
	int		i;
	int		j;
	char	**buff;

	i = 0;
	j = 0;
	buff = ft_split(line, ' ');
	while (buff[i] != NULL)
	{
		if (is_terminator(buff[i], 0) == 1)
			return (0);
		i++;
	}
	if (ft_strlen(buff[0]) != 4)
		return (0);
	else if (i == 1)
		exit(0);
	j = ft_exitoi(buff[1]);
	if (j == 257)
	{
		printf("bash: exit: numeric argument required\n");
		exit(255);
	}
	if (i > 2)
	{
		printf("bbshell: exit: too many arguments\n");
		return (0);
	}
	else
		exit(j);
	return (-1);
}

int	main(int argc, char **argv, char **o_env)
{
	char	*line;

	(void)argc;
	(void)argv;
	init_g(o_env);
	activate_signals();
	while (1)
	{
		line = readline("BBShell >$ ");
		if (line == NULL)
			exit(0);
		if (!line || line[0] == '\0')
			continue ;
		else
		{
			if (ft_strncmp(line, "exit", 4) == 0)
				if (ft_exit(line) == -1)
					continue ;
			if (take_care(line) == -1)
				continue ;
		}
		free(line);
	}
	return (garbage_collector());
}

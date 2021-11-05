/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:52:03 by malmeida          #+#    #+#             */
/*   Updated: 2021/11/05 15:11:25 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_cmds {
	char	**command;
	int		type;
}		t_cmds;



int	is_terminator(char j)
{
	if (j == '|' || j == '<' || j == '>' || j == ';' || j == '\0')
		return (1);
	else
		return (0);
}

// ver quantos comandos no total existem, para depois alocar t_cmds[n] consoante
// o numero de comandos
int	command_counter(char *line)
{
	int	counter;
	int	i;

	counter = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
			i++;
		}
		if (is_terminator(line[i]))
		{
			counter++;
			i++;
			if (is_terminator(line[i]))
				i++;
		}
		i++;
	}
	return (counter);
}

//parser atribui os comandos para structs t_cmd
void	parser(char *line, int n)
{
	t_cmds	*cmd;
	int		quotes_open;
	int		i;
	int		j;


	cmd = malloc(sizeof(t_cmds) * command_counter(line));
	i = 0;
	while (line[i])
	{
		while (is_terminator(line[i]))
		{
			
			// avancar enquanto e tudo o mesmo comando, e meter tudo numa struct t_cmds
		}
	//node++;
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	printf("There are %d commands here\n", command_counter(str));
	return (0);
}


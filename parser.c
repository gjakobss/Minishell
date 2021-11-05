/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:52:03 by malmeida          #+#    #+#             */
/*   Updated: 2021/11/05 15:53:14 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_cmds {
	char	*full_line;
	char	**command;
	int		type;
}		t_cmds;

/*		LIBFT STUFF		*/

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	ptr = (char *)malloc(sizeof(*ptr) * len + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	s1;
	unsigned int	s2;
	unsigned int	rlen;

	if (!s)
		return (0);
	rlen = ft_strlen(s);
	if (start >= rlen)
	{
		str = malloc(sizeof(char));
		*str = '\0';
		return (str);
	}
	if (rlen < len)
		return (ft_strdup(s + start));
	str = (char *)malloc(len + 1);
	if (!(str))
		return (0);
	s1 = start;
	s2 = 0;
	while (s1 < rlen && s2 < len)
		str[s2++] = s[s1++];
	str[s2] = '\0';
	return (str);
}

/*		LIBFT STUFF		*/

int	is_terminator(char j)
{
	if (j == '|' || j == '<' || j == '>' || j == ';' || j == '\0')
		return (1);
	else
		return (0);
}

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

void	assign_line(t_cmds *cmd, char *line)
{
	int	i;
	int	j;
	int	start;
	int	len;

	j = 0;
	i = 0;
	while (line[i])
	{
		start = i;
		while (!is_terminator(line[i]))
		{
			if (line[i] == '"')
			{
				i++;
				while (line[i] != '"')
					i++;
			}
			i++;
		}
		len = i - start - 1;
		cmd[j].full_line = ft_substr(line, start, len);
		j++;
		i++;
	}
}

//1o aloca n structs t_cmds, sendo n o numero de comandos na line
//2o (assign_line) parte line em comandos, e mete cada comando dentro da sua struct
void	parser(char *line)
{
	t_cmds	*cmd;
	int		num_cmds;
	int		i;

	num_cmds = command_counter(line);
	cmd = malloc(sizeof(t_cmds) * num_cmds);
	assign_line(cmd, line);
	i = -1;
	while (++i < num_cmds)
		printf("cmd %d is %s\n", i + 1, cmd[i].full_line);
}

int	main(int ac, char **av)
{
	parser(av[1]);
	return (0);
}

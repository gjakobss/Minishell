/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:27:15 by gjakobss          #+#    #+#             */
/*   Updated: 2021/03/05 15:13:29 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	writer(char **line, char **str, int fd)
{
	int		length;
	char	*temp;

	length = 0;
	while (str[fd][length] != '\0' && str[fd][length] != '\n')
		length++;
	if (str[fd][length] == '\n')
	{
		*line = ft_substr(str[fd], 0, length);
		temp = ft_substr(str[fd], length + 1, ft_strlen(str[fd]) - length);
		free(str[fd]);
		str[fd] = temp;
		return (1);
	}
	else
	{
		*line = ft_strdup(str[fd]);
		*line = ft_strjoin(*line, "\n");
		free(str[fd]);
		str[fd] = 0;
		return (0);
	}
}

static int	backup(int readval, char **line, char **str, int fd)
{
	if (!(readval) && str[fd] == NULL)
	{
		*line = strdup("");
		return (0);
	}
	if (readval == -1)
		return (-1);
	return (writer(line, str, fd));
}

int	get_next_line(int fd, char **line)
{
	static char	*str[100000];
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	int			readval;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	readval = read(fd, buffer, BUFFER_SIZE);
	while (readval > 0)
	{
		buffer[readval] = '\0';
		if (!str[fd])
			str[fd] = ft_strdup("");
		temp = ft_strjoin(str[fd], buffer);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(str[fd], '\n'))
			break ;
		readval = read(fd, buffer, BUFFER_SIZE);
	}
	return (backup(readval, line, str, fd));
}

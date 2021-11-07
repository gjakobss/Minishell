/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:02:16 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/22 15:26:41 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	free_all(char **split, int j)
{
	while (j >= 0)
	{
		free(split[j]);
		j++;
	}
	free(split);
	return (0);
}

static int	get_len(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	if (!s)
		return (0);
	while (*s == c && s[i + 1] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			word++;
		}
		i++;
	}
	if (s[0] != c)
		word += 1;
	return (word);
}

static char	*copy(char *split, const char *s, int i, int k)
{
	int	car;

	car = 0;
	while (k < i)
	{
		split[car++] = s[k++];
	}
	split[car] = '\0';
	return (split);
}

static int	alloc_and_copy(char **split, char const *s, char c, int i)
{
	int	j;
	int	k;
	int	car;

	j = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (1);
	while (s[i] != '\0')
	{
		car = 0;
		while (s[i] != c && s[i] != '\0' && car++ <= i)
			i++;
		split[j] = malloc(sizeof(char) * (car + 1));
		if (!split)
			return (free_all(split, j));
		k = i - car;
		split[j] = copy(split[j], s, i, k);
		while (s[i] == c && s[i] != '\0')
			i++;
		j++;
	}
	split[j] = NULL;
	return (j);
}

char		**ft_split(char const *s, char c)
{
	char	**split;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (get_len(s, c) + 1));
	if (!s || !split)
		return (NULL);
	split[get_len(s, c)] = NULL;
	if (alloc_and_copy(split, s, c, i) == 0)
		return (NULL);
	return (split);
}

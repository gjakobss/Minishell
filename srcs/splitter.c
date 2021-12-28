/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:18:36 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/14 12:25:27 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '"')
		return (DQUOTES);
	if (c == '\'')
		return (SQUOTES);
	else
		return (0);
}

static int	count_words(char const *s, char c)
{
	int	word_count;
	int	i;
	int	quote;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			quote = is_quote(s[i]);
			if (quote)
			{
				i++;
				while (is_quote(s[i]) != quote)
					i++;
			}
			word_count++;
		}
		while (s[i] && (s[i] != c))
			i++;
	}
	return (word_count);
}

int	splitter2(int j, const char *s, char c)
{
	int	quote;
	int	arr_index;

	arr_index = 0;
	while (s[j] && s[j] != c)
	{
		quote = is_quote(s[j]);
		if (quote)
		{
			j++;
			while (is_quote(s[j]) != quote)
				j++;
		}
		j++;
	}
	return (j);
}

char	**splitter(char const *s, char c)
{
	int		j;
	int		i;
	int		arr_index;
	char	**array;

	if (!s)
		return (0);
	array = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!(array))
		return (0);
	array[count_words(s, c)] = NULL;
	arr_index = 0;
	while (*s && *s == c)
		s++;
	j = 0;
	while (s[j])
	{
		i = j;
		j = splitter2(j, s, c);
		array[arr_index++] = ft_substr(s, i, j - i);
		while (s[j] && s[j] == c)
			j++;
	}
	return (array);
}

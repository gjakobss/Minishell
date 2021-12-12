/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 23:18:36 by malmeida          #+#    #+#             */
/*   Updated: 2021/12/12 00:09:41 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_quote(char c)
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

char	**splitter(char const *s, char c)
{
	int		i;
	int		j;
	int		arr_index;
	char	**array;

	if (!s)
		return (0);
	array = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!(array))
		return (0);
	array[count_words(s, c)] = 0;
	arr_index = 0;
	while (*s && *s == c)
		s++;
	j = 0;
	while (s[j])
	{
		i = j;
		while (s[j] && s[j] != c)
			j++;
		array[arr_index++] = ft_substr(s, i, j - i);
		while (s[j] && s[j] == c)
			j++;
	}
	return (array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:04:49 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/15 12:57:27 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_counter(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (c == 0)
	{
		return (NULL);
	}
	return (NULL);
}

static int	ft_start(char	const *s1, char	const *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_counter(set, s1[i]) == NULL)
			return (i);
		i++;
	}
	return (i);
}

static int	ft_end(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen((char *)s1);
	while (i <= len)
	{
		if (ft_counter(set, s1[len - i]) == NULL)
			return (len - i);
		i++;
	}
	return (len - i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*newstr;
	int		i;

	start = ft_start(s1, set);
	end = ft_end(s1, set);
	i = 0;
	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	if (start >= end)
		return (ft_strdup(""));
	newstr = (char*)malloc((end - start + 2) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	while (start + i <= end)
	{
		newstr[i] = s1[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

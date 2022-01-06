/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:52:29 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/19 16:53:37 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(const char *haystack, const char *needle)
{
	int	counter;

	counter = 0;
	while (*haystack != '\0')
	{
		if (*haystack == needle[0])
			counter++;
		haystack++;
	}
	return (counter);
}

static char	*ft_find(const char *haystack, const char *needle, \
					size_t x, size_t len)
{
	size_t	z;
	size_t	t;
	size_t	y;
	int		counter;

	counter = ft_counter(haystack, needle);
	t = 0;
	z = 0;
	y = 0;
	while (counter > 0)
	{
		while (haystack[x + y] == needle[y] && haystack[x + y] != '\0'
			&& needle[y] != '\0' && x + y < len)
		{
			y++;
		}
		if (needle[y] == '\0')
			return ((char *)&haystack[x]);
		else if (haystack[x] == needle[0])
			counter--;
		x++;
		y = 0;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	while (needle[y] != '\0')
	{
		while (haystack[x] != '\0' && x < len)
		{
			if (haystack[x] == needle[y])
				return (ft_find(haystack, needle, x, len));
			x++;
		}
		x = 0;
		y++;
	}
	return (NULL);
}

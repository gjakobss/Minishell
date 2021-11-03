/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:04:36 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/19 15:34:59 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	slen;
	char	*ptr;
	int		i;

	i = 0;
	ptr = 0;
	slen = 0;
	str = (char *)s;
	while (s[slen] != '\0')
		slen++;
	if (c == '\0')
	{
		return ((char *)s + slen);
	}
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			ptr = &str[i];
		}
		i++;
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:05:01 by gjakobss          #+#    #+#             */
/*   Updated: 2021/11/09 11:21:25 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	check_len(char const *s, size_t len)
{
	if ((int)len > ft_strlen(s))
		return (ft_strlen(s));
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((int)start > ft_strlen(s))
	{
		ptr = malloc(sizeof(char));
		if (ptr == NULL)
			return (NULL);
		*ptr = '\0';
		return (ptr);
	}
	ptr = malloc((check_len(s, len) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len && (int)(start + i) < ft_strlen(s))
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

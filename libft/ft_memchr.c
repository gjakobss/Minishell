/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:00:25 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/15 11:00:27 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	size_t			i;

	i = 0;
	while (i < n)
	{
		a = (unsigned char *)s;
		if (*a == (unsigned char)c)
		{
			return (a);
		}
		s++;
		i++;
		a++;
	}
	return (NULL);
}

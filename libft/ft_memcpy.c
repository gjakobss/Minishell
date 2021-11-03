/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:00:49 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/15 12:55:45 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*a;
	char	*b;
	int		i;

	a = (char *)dst;
	b = (char *)src;
	i = 0;
	if (!src && !dst)
		return (dst);
	while (n > 0)
	{
		a[i] = b[i];
		i++;
		n--;
	}
	return (dst);
}

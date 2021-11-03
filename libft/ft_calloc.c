/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:56:34 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/15 11:06:55 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	length;

	length = size * count;
	ptr = (char *)malloc(length);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, length);
	return (ptr);
}

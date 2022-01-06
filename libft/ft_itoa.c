/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:58:54 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/22 10:34:15 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_counter(int n)
{
	int			counter;
	long int	i;

	counter = 0;
	i = n;
	if (i < 0)
	{
		counter = 1;
		i *= -1;
	}
	while (i >= 10)
	{
		i = (i / 10);
		counter++;
	}
	return (counter + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		strsize;

	strsize = ft_counter(n);
	str = malloc(sizeof(char) * (strsize + 1));
	if (!str)
		return (NULL);
	str[strsize] = '\0';
	if (n < 0)
		str[0] = '-';
	if (n < 0)
		n *= -1;
	strsize -= 1;
	while (n >= 10 && strsize >= 0)
	{
		str[strsize--] = (n % 10) + 48;
		n /= 10;
	}
	str[strsize] = n + 48;
	return (str);
}

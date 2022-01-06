/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:56:19 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/19 15:30:42 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v' \
			|| c == '\r' || c == '\f')
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	nmr;
	int			signal;

	i = 0;
	nmr = 0;
	signal = 1;
	while (ft_is_space(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nmr = nmr * 10 + ((str[i++] - 48));
	}
	nmr = nmr * signal;
	if (nmr > 2147483647)
		return (-1);
	else if (nmr < -2147483648)
		return (0);
	return (nmr);
}

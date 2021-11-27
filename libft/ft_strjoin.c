/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:02:53 by gjakobss          #+#    #+#             */
/*   Updated: 2021/02/19 15:33:06 by gjakobss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str3join(char const *s1, char const *s2, char const *s3)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	len = (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	ptr = (char*)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (!s1)
		return (NULL);
	if (!s2)
		return ((char *)s1);
	while (*s1 != '\0')
	{
		ptr[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
		ptr[i++] = *s2++;
	while (*s3 != '\0')
		ptr[i++] = *s3++;
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	ptr = (char*)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (!s1)
		return (NULL);
	if (!s2)
		return ((char *)s1);
	while (*s1 != '\0')
	{
		ptr[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

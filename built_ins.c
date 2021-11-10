/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:08:06 by malmeida          #+#    #+#             */
/*   Updated: 2021/11/10 22:14:55 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(void)
{
	int	i;

	i = 0;
	while (g_mini.env[i])
		printf("%s\n", g_mini.env[i++]);
}

void	bi_pwd(void)
{
	char	str[999];

	getcwd(str, 999);
	printf("%s\n", str);
}

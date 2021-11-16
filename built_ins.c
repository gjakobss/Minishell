/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:08:06 by malmeida          #+#    #+#             */
/*   Updated: 2021/11/16 13:48:14 by malmeida         ###   ########.fr       */
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

void	bi_cd(char *str)
{
	int	ret;

	if ((!str) || (str[0] == '~' && str[1] == '\0'))
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(str);
	if (ret == -1)
		printf("Error changing directory\n");
}

void	bi_echo(char **str)
{
	int	n_flag;

	if (str[1][0] == '-' && str[1][1] == 'n')
		n_flag = 1;
	else
		n_flag = 0;

}

/*

void	bi_export(char *str)
{
	int		i;
	char	**new_env = NULL;

	i = 0;
	while (g_mini.env[i] != NULL)
	{
		new_env[i] = ft_strdup(g_mini.env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	i = 0;
	while (g_mini.env[i] != NULL)
	{
		free(g_mini.env[i]);
		i++;
	}
	g_mini.env = new_env;
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:08:06 by malmeida          #+#    #+#             */
/*   Updated: 2021/11/17 22:19:02 by malmeida         ###   ########.fr       */
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

//	Esta funcao tira as aspas dos argumentos do echo, tipo se lhe passares
//	echo "joao", queres que ele imprima so joao em vez de "joao"
//	Depois dou-lhe um nome mais serio
//	Ta meio fodido isto ainda

static char	*real_aspas_remover(char *str)
{
	char	**ptr;
	int		i;
//	int		j;
	int		len;

	len = 0;
	i = 0;
	while (str[len])
		len++;
	while (str[i])
	{
		if (str[i] == '"')
			break;
		i++;
	}
	if (str[i] == '\0')
		return (str);
	else
		ptr = ft_split(str, '"');
	i = 1;
//		ptr = (char *)malloc(sizeof(char) * len - 1);
//	i = 0;
//	j = 1;
//	while (i < len - 2)
//	{
//		ptr[i] = str[j];
//		i++;
//		j++;
//	}
//	ptr[i] = '\0';
	return (*ptr);
}

static void	aspas_remover(char **str, int n_flag)
{
	int		i;

	if (n_flag)
		i = 2;
	else
		i = 1;
	while (str[i])
	{
		str[i] = real_aspas_remover(str[i]);
		i++;
	}
}

void	bi_echo(char **str)
{
	int	n_flag;
	int	i;

	if (str[1][0] == '-' && str[1][1] == 'n')
	{
		n_flag = 1;
		i = 2;
	}
	else
	{
		n_flag = 0;
		i = 1;
	}
	aspas_remover(str, n_flag);
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
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

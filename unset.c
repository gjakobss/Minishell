#include "minishell.h"

void	rm_from_exp(int j)
{
	char	*temp;

	while (g_mini.exp[j + 1] != NULL)
	{
		temp = g_mini.exp[j];
		g_mini.exp[j] = g_mini.exp[j + 1];
		g_mini.exp[j + 1] = temp;
		j++;
	}
	g_mini.exp[j] = NULL;
	free(g_mini.exp[j + 1]);
}

void	rm_from_env(int j)
{
	char	*temp;

	while (g_mini.env[j + 1])
	{
		temp = g_mini.env[j];
		g_mini.env[j] = g_mini.env[j + 1];
		g_mini.env[j + 1] = temp;
		j++;
	}
	g_mini.env[j] = NULL;
	free(g_mini.env[j + 1]);
}

void	bi_unset(char **buff)
{
	int j;
	int	i;
	int	len;

	i = 0;
	while(buff[++i])
	{
		j = -1;
		len = ft_strlen(buff[i]);
		while (g_mini.exp[++j])
			if (ft_strncmp(buff[i], g_mini.exp[j], len - 1) == 0)
				rm_from_exp(j);
		j = -1;
		while(g_mini.env[++j])
			if (ft_strncmp(buff[i], g_mini.env[j], len - 1) == 0)
				rm_from_env(j);
	}
}

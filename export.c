#include "minishell.h"

void	write_export(void)
{
	int	i;

	i = 0;
	while(g_mini.exp[i])
		printf("declare -x %s\n", g_mini.exp[i++]);
	return ;
}

int	get_env_from_export(char	**buff, int j)
{
	int		i;
	int		checker;
	char	**new_env;

	i = -1;
	checker = 0;
	while(buff[++j] != NULL)
		if (ft_strchr(buff[j], 61) != NULL)
			break;
	if (buff[j] == NULL)
		return (j);
	else
	{
		while (buff[j][checker] != '=')
			checker++;
		while (g_mini.env[++i] != NULL)
		{
			if (ft_strncmp(buff[j], g_mini.env[i], checker) == 0)
			{
				checker = -1;
				g_mini.env[i] = buff[j];
				return (j);
			}
		}
	}
	new_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (g_mini.env[++i] != NULL)
		new_env[i] = ft_strdup(g_mini.env[i]);
	new_env[i++] = ft_strdup(buff[j]);
	new_env[i] = NULL;
	i = 0;
	free(g_mini.env);
	g_mini.env = new_env;
	return(j);
}


void	bi_export(char **buff)
{
	int		j;
	int		i;
	int checker;

	j = 0;
	i = -1;
	if (!buff[1])
	{
		write_export();
		return ;
	}
	while (buff[++j] != NULL)
	{

		i = -1;
		checker = 0;
		while (buff[j][checker] != '=')
			checker++;
		while (g_mini.exp[++i])
		{
			if (ft_strncmp(buff[j], g_mini.exp[i], checker) == 0)
			{
				checker = -1;
				g_mini.exp[i] = buff[j];
				g_mini.exp = exp_organizer(g_mini.exp, NULL);
				break ;
			}
		}
		if (checker != -1)
			g_mini.exp = exp_organizer(g_mini.exp, buff[j]);
	}
	j = 0;
	while(buff[j] != NULL)
		j = get_env_from_export(buff, j);
}

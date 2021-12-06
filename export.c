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
	char	**new_env;

	i = 0;

	while(buff[++j] != NULL)
		if (ft_strchr(buff[j], 61) != NULL)
			break;
	if (buff[j] == NULL)
		return (j);
	while (g_mini.env[i] != NULL)
		i++;
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

	j = 0;
	if (!buff[1])
	{
		write_export();
		return ;
	}
	while (buff[++j] != NULL)
		g_mini.exp = exp_organizer(g_mini.exp, buff[j]);
	j = 0;
	while(buff[j] != NULL)
	{
		j = get_env_from_export(buff, j);
	}
}

#include "minishell.h"

void	bi_export(char **buff)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (buff[j] != NULL)
		j++;
	while (g_mini.env[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + j));
	i = -1;
	while (g_mini.env[++i] != NULL)
		new_env[i] = ft_strdup(g_mini.env[i]);
	j = 1;
	while (buff[j] != NULL)
		new_env[i++] = ft_strdup(buff[j++]);
	new_env[i] = NULL;
	i = 0;
	free(g_mini.env);
	g_mini.env = new_env;
}

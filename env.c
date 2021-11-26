#include "minishell.h"

void	bi_env(void)
{
	int	i;

	i = 0;
	while (g_mini.env[i] != NULL)
		printf("%s\n", g_mini.env[i++]);
}

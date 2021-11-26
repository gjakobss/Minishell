#include "minishell.h"

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


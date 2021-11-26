#include "minishell.h"

void	bi_pwd(void)
{
	char	str[999];

	getcwd(str, 999);
	printf("%s\n", str);
}
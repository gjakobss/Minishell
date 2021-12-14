#include "minishell.h"

int	update_pwd(char *old, char *new)
{
	int i;

	i = 0;
	while (g_mini.env[i] && ft_strncmp(g_mini.env[i], "PWD", 3) != 0)
		i++;
	if (g_mini.env[i] != NULL)
		g_mini.env[i] = ft_strjoin("PWD=", new);
	i = 0;
	while (g_mini.env[i] && ft_strncmp(g_mini.env[i], "OLDPWD", 6) != 0)
		i++;
	if (g_mini.env[i] != NULL)
		g_mini.env[i] = ft_strjoin("OLDPWD=", old);
	return (0);
}

void	bi_cd(char *str)
{
	char new_pwd[1024];
	char *old_pwd;
	int	ret;

	old_pwd = getenv("PWD");
	if ((!str) || (str[0] == '~' && str[1] == '\0'))
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(str);
	if (ret == -1)
		printf("Error changing directory\n");
	getcwd(new_pwd, 1024);
	update_pwd(old_pwd, new_pwd);
}

#include "minishell.h"

char	*exp_organizer2(char **ret, int i)
{
	int	j;
	int	x;

	j = 0;
	while (ret[++j] != NULL)
	{
		if (i == j)
			j++;
		if (ret[j] == NULL)
			break ;
		if(ret[i][0] > ret[j][0] && ft_strcmp(ret[j], "0") != 0)
			i = j;
		else if (ret[i][0] == ret[j][0] && ft_strcmp(ret[j], "0") != 0)
		{
			x = 0;
			while(ret[i][x] != '\0' && ret[j][x] != '\0' && ret[i][x] == ret[j][x])
				x++;
			if (ret[j][x] == '\0' || ret[i][x] > ret[j][x])
				i = j;
		}
	}
	return (ret[i]);
}

char	**exp_organizer(char **exp, char *str)
{
	char	**ret;
	int		i;
	int		j;
	int		y;

	i = 0;
	j = 0;
	y = 0;
	while (exp[i])
		i++;
	if (str != NULL)
		i++;
	ret = malloc(sizeof(char *) * (i + 1));
	i = 0;
	if (str)
		ret[i++] = str;
	while (exp[j])
		ret[i++] = exp[j++];
	ret[i] = NULL;
	exp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ret[i] != NULL)
	{
		j = 0;
		exp[y] = exp_organizer2(ret, i);
		while (ft_strcmp(ret[j], exp[y]) != 0)
			j++;
		if (ft_strcmp(ret[j], exp[y]) == 0)
			ret[j] = "0";
		y++;
		while (ret[i] != NULL && ft_strcmp(ret[i], "0") == 0)
			i++;
	}
	exp[y] = NULL;
	return (exp);
}

void	exec_one_bi(int x)
{
	char	*str;

	str = g_mini.cmd[x].command[0];
	if (!ft_strcmp(str, "cd"))
		bi_cd(g_mini.cmd[x].command[1]);
	if (!ft_strcmp(str, "pwd"))
		bi_pwd();
	if (!ft_strcmp(str, "env"))
		bi_env();
	if (!ft_strcmp(str, "echo"))
		bi_echo(g_mini.cmd[x].command);
	if (!ft_strcmp(str, "export"))
		bi_export(g_mini.cmd[x].command);
	if (!ft_strcmp(str, "unset"))
		bi_unset(g_mini.cmd[x].command);
}

int	is_builtin(int x)
{
	char	*str;

	str = g_mini.cmd[x].command[0];
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "cd"))
		return (1);
	return (0);
}

int	get_bin_path(void)
{
	int	i;

	i = 0;
//	usar o getenv("PATH")
	while (g_mini.env[i] != NULL)
	{
		if (g_mini.env[i][0] == 'P' && g_mini.env[i][1] == 'A')
			break ;
		i++;
	}
	if (g_mini.env[i] == NULL && is_builtin(0) == 0)
		return (-1);
	else if (g_mini.env[i] == NULL && is_builtin(0) == 1)
		return (0);
	g_mini.bin_paths = ft_split(g_mini.env[i] + 5, ':');
	return (0);
}

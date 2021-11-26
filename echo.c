#include "minishell.h"

//	Esta funcao tira as aspas dos argumentos do echo, tipo se lhe passares
//	echo "joao", queres que ele imprima so joao em vez de "joao"
//	Depois dou-lhe um nome mais serio
//	Ta meio fodido isto ainda

static char	*real_aspas_remover(char *str)
{
	char	**ptr;
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			c = '"';
			break ;
		}
		else if (str[i] == '\'')
		{
			c = '\'';
			break ;
		}
		i++;
	}
	if (str[i] == '\0')
		return (str);
	else
		ptr = ft_split(str, c);
//	if (ptr[1] != NULL)
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
//		if (str[i] == '$')
		str[i] = real_aspas_remover(str[i]);
		i++;
	}
}

void	bi_echo(char **str)
{
	int	n_flag;
	int	i;

	if (str[1] == NULL)
	{
		printf("\n");
		return ;
	}
	n_flag = 0;
	i = 0;
	if (str[1][0] == '-' && str[1][1] == 'n')
	{
		n_flag = 1;
		i = 1;
	}
	aspas_remover(str, n_flag);
	while (str[++i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}

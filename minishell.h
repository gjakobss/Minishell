#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>

# include "libft/libft.h"

typedef struct	s_cmds {
	char	*full_line;
	char	**command;
	int		type;
}		t_cmds;

typedef struct	s_mini
{
	char	**bin_paths;
	char	**env;
	int		**pipefd;
	int		pipes;
	int		s_quotes;
	int		d_quotes;
//	int		pipefd[2];
	t_cmds	*cmd;
}				t_mini;

t_mini	g_mini;

t_cmds	*parser(char *line);

void	bi_env(void);
void	bi_pwd(void);
void	bi_cd(char *str);
void	bi_echo(char **str);

#endif

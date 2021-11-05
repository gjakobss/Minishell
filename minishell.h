#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/wait.h>

# include "libft/libft.h"

typedef struct	s_mini
{
	char	**bin_paths;
	char	**env;
	char	**commands;
	int		pipes;
	int		quotes;
	int		pipefd[2];

}				t_mini;

t_mini	g_mini;

#endif

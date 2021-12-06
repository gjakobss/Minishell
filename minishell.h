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

typedef struct s_cmds {
	char	*full_line;
	char	**command;
	int		type;
}		t_cmds;

typedef struct s_mini
{
	char	**bin_paths;
	char	**env;
	char	**exp;
	int		**pipefd;
	int		pipes;
	int		s_quotes;
	int		d_quotes;
	int		semi_col;
	int		dollar;
	t_cmds	*cmd;
}				t_mini;

t_mini	g_mini;

t_cmds	*parser(char *line);
void	bi_env(void);
void	bi_pwd(void);
void	bi_cd(char *str);
void	bi_echo(char **str);
void	bi_export(char **buff);
void	bi_unset(char **buff);
int		send_to_exec(void);
int		is_builtin(int x);
void	exec_one_bi(int x);
char	**exp_organizer(char **exp, char *str);
char	*exp_organizer2(char **ret, int i);
char	*exp_organizer2(char **ret, int i);
char	**exp_organizer(char **exp, char *str);
void	exec_one_bi(int x);
int		is_builtin(int x);
int		get_bin_path(void);
#endif

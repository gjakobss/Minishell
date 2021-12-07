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

# define LEAF 1
# define BRANCH 2

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
	t_tree          head;
}				t_mini;

typedef struct s_branch {
        int             op;
        struct s_tree   *left;
        struct s_tree   *right;
}           t_branch;

typedef struct  s_leaf   {
    char    *full_line;
    char    **command;
    int     args;
}           t_leaf;

typedef struct  s_tree {
    int     type;
    union {
        t_branch    branch;
        t_leaf      leaf;
    }
    struct s_tree   *prev;
}           t_tree;

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

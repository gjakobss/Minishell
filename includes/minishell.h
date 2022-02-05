/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjakobss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:26:14 by gjakobss          #+#    #+#             */
/*   Updated: 2022/01/07 14:09:17 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

# include "../libft/libft.h"
# include "get_next_line.h"

# define PIPE 1
# define GREATER 2
# define SMALLER 3
# define DGREATER 4
# define DSMALLER 5
# define EOL 6
# define DQUOTES 7
# define SQUOTES 8

typedef struct s_vars {
	int	i;
	int	j;
	int	z;
	int	size;
}		t_vars;

typedef struct s_var {
	int		i;
	int		j;
	int		len;
	char	*copy;
}		t_var;

typedef struct s_chars {
	char	*line;
	char	*temp;
	char	*sub;
	int		i;
}		t_chars;

typedef struct s_cmds {
	char	*full_line;
	char	**command;
	int		op;
	char	*heredoc;
	int		hdop;
}		t_cmds;

typedef struct s_mini
{
	char			**bin_paths;
	char			**env;
	char			**exp;
	int				**pipefd;
	int				pipes;
	int				s_quotes;
	int				d_quotes;
	int				semi_col;
	int				dollar;
	t_cmds			*cmd;
	int				num_cmds;
	int				sig_int;
	int				status;
	int				pid;
	int				child;
	struct termios	t;
}				t_mini;

typedef struct s_expand
{
	char	*full;
	char	*before;
	char	*var;
	char	*after;
}				t_expand;

t_mini	g_mini;

/*		Built-ins		*/
int		bi_env(void);
int		bi_pwd(void);
int		bi_cd(int c, char *str, int index);
int		bi_echo(int x, char **str);
int		bi_export(char **buff, int index);
int		bi_unset(char **buff);

/*		Arg Validation	*/
int		arg_validation(char **line);
int		quotes_checker(char *line);
void	operators_count(char *line);
int		check_commands(char **line, int i);

/*		Arg Parser	*/
t_cmds	*parser(char *line);
int		is_terminator(char *line, int j);
int		command_counter(char *line);
void	check_brackets_expansion(char **line);
char	*correct_brackets(char *line);

/*		Quotes Parsing		*/
void	remove_beginning_quotes(char **cmd);
void	remove_middle_quotes(char **cmd);
void	quote_remover(char **cmd, int *i, int quotes);

/*		Lexer		*/
void	quotes_skipper(char *line, int *i, int quotes);
int		assign_operator(char *line, int *i);
void	assign_line(t_cmds *cmd, char *line, int x, int z);
void	lexer(t_cmds *cmd, char *line);

/*		Expand Variables	*/
void	replace_command(char **line, t_expand str);
char	*strreplace_var(char *str);
void	expand_variables(char **line, int start);
void	expander(t_cmds *cmd);

/*		Splitter		*/
int		is_quote(char c);
int		splitter2(int j, const char *s, char c);
char	**splitter(char const *s, char c);

/*		Signals		*/
void	activate_signals(void);

/*		Exec		*/
int		exec_one(int c);
int		exec_com_one(int c, int index, int i);
int		exec_com_mid(int c, int index);
int		exec_last_com(int c, int index);
int		send_to_exec(void);

int		exec_one2(int c, int j, int i);
int		exec_com2(int c, int i);
int		divergent(int c, int index, int id, int temp);
int		divergent2(int c, int id, int index);
int		one_time(int c, int index, int temp);
int		multi_exec(int c, int index, int i);
char	**get_sub(int c, int x, int temp, int i);
/*		Minishell	*/
int		garbage_collector(int i);
int		take_care(char *line);
void	init_g(char **o_env);
char	**init_env(char **o_env);

/*		Redirections	*/
int		send_output2(int fd, int index, int c);
int		send_output(int c, int index, int i);
int		append_output(int c, int index, int i);
int		send_input(int c, int index);
int		wait_input(int c, int index);

/*		Utils	*/
char	**get_quotes(char **exp, char *str);
char	*exp_organizer2(char **ret, int i);
char	**exp_organizer(char **exp, char *str, int i, int y);
int		exec_one_bi(int x, int index);
int		is_builtin(int x);
int		get_bin_path(void);
int		cat_fix(int c);
void	exec_cat(int c, int nmr);
char	*get_env(char *str);
char	**subarr(int c, int x);
void	write_export(void);
void	get_new_env(char **buff, int i, int j);
int		ft_strchrlen(char	*str, char c);
void	exit_helper(int j, int i);
void	safety_check(char **str, int j);
void	null_stringer(char **str);
void	assign_variables(t_var *v, char *str);
void	variable_assigner(t_chars *x);
void	looper(t_var *v, char **str);
char	*replace_var(char *str);
void	if_ls(t_chars *x, int c);

#endif
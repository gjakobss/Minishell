gcc -Wall -Wextra -Werror minishell.c cd.c env.c exec.c export.c echo.c pwd.c parser.c unset.c utils.c arg_validation.c redirections.c -lreadline get_next_line.c libft/ft_split.c ./libft/libft.a -g -fsanitize=address -o bbshell

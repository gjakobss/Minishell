gcc -Wall -Wextra -Werror minishell.c cd.c env.c export.c echo.c pwd.c parser.c -lreadline libft/ft_split.c ./libft/libft.a -g -fsanitize=address -o bbshell

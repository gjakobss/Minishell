gcc -Wall -Wextra -Werror minishell.c parser.c built_ins.c -lreadline libft/ft_split.c ./libft/libft.a -g -fsanitize=address -o bbshell

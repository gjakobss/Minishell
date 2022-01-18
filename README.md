# minishell

The objective of this project is to create a shell, bbshell.

TO DO

SIGNALS
- CTRL+\ needs some checking

- CTRL+D should print exit

- CTRL+C should print ^C sometimes

- check signals on heredoc


- Check export starting with numbers
	§ Should be okay (needs that really hard testing with fucked up arguments, but it looks good)


- Validation for export needed


- echo a | exit should do nothing and exit | echo a should printf a and NOT quit
	§ echo a | exit is not printing anything anymore. exit | echo a does print. so, its working


- exit must quit if it has multiple arguments and the first is not a number. if the first arg is a nmbr it does not quit
	§ Looks good!


- echo ~ must expand
	§Fixed


- check cd -
	§ Fixed.

- check parsing for ech""o

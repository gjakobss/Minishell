int	check_commands(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '|' || line[i] == '<' || line[i] == '>' || line[i] == ';' || line[i] == ' ')
		{
			while (line[i] != '\0')
			{
				if ((line[i] >= 'a' && line[i] <= 'z')
					|| (line[i] >= 'A' && line[i] <= 'Z'))
					break;
			i++;
			}
			if (line[i] == '\0')
			{
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

// not checking for double << or >>
int is_terminator(char j)
{
    if (j == '"')
        g_mini.d_quotes += 1;
    else if (j == '\'')
        g_mine.s_quotes += 1;
    else if (j == '|' || j == '<' || j == '>' || j == ';')
    {
        if (j == '|')
            g_mini.pipes += 1;
        if (j == ';')
            g_mine.semi_col += 1;
        return (1);
    }
    return (0);
}

t_tree init_branch(void)
{
	t_tree	*new;

	new = NULL;
	new = malloc(sizeof(t_tree));
	if (!new)
		return (1);
	new->type = BRANCH;
	new->branch.op = 0;
	new->branch.left = NULL;
	new->branch.right = NULL;
	new->prev = NULL;
	return (new);
}

t_tree	init_leaf(void)
{
	t_tree	*new;

	new = NULL;
	new = malloc(sizeof(t_tree));
	if (!new)
		return (1);
	new->type = LEAF;
	new->leaf.full_line = NULL;
	new->leaf.command = NULL;
	new->leaf.args = 0;
	new->prev = NULL;
	return (new);
}

void assign_leaf(t_tree *current, char *line)
{
	int	i;

	current->leaf.command = ft_split(line, ' ');
	i = 0;
	while (current->leaf.command[i])
		i++;
	current->leaf.command[i] = NULL;
	current->leaf.args = i;
}

void	skip_quotes(char *line, int *i)
{
	(*i)++;
	while (line[*i] != '"' && line[*i] != '\0')
		(*i)++;
	if (line[*i] == '"')
		g_mini.d_quotes += 1;
}

//  maybe check before hand the whole input to see if there are pairs of aspas
t_tree tree_builder(char *line)
{
    t_tree  *current;
    int i;

	current = g_mini.head;
    i = 0;
    while (line[i])
    {
        start = i;
        while (!is_terminator(line[i]))
        {
			if (line[i] == '"')
				skip_quotes(line, &i);
            if (line[i] == '\0')
                break ;
            i++;
        }
		if (line[i] == '\0')
		{

		}
        len = i - start;
        if (len > 0)
            assign_leaf(ft_substr(line, start, len));
    }
}

void  parsing(char *line)
{
    if (check_commands(line) == -1)
        return (NULL);
	g_mini.head = init_leaf();
    tree_builder(line);


}

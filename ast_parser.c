
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

//  maybe check before hand the whole input to see if there are pairs of aspas
t_tree tree_builder(char *line)
{
    t_tree  current;
    int i;
    int ops;

    ops = 0;
    i = 0;
    while (line[i])
    {
        start = i;
        while (!is_terminator(line[i]))
        {
            if (line[i] == '"')
            {
                i++;
                while (line[i] != '"' && line[i] != '\0')
                    i++;
                if (line[i] == '"')
                    g_mini.d_quotes += 1;
            }
            if (line[i] == '\0')
                break ;
            i++;
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
    g_mini.head = malloc(sizeof(t_tree));
    g_mini.head = tree_builder(line);

}

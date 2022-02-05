/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:38:26 by malmeida          #+#    #+#             */
/*   Updated: 2022/02/05 16:38:27 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	null_stringer(char **str)
{
	*str = NULL;
	*str = malloc(sizeof(char));
	(*str)[0] = '\0';
}

void	assign_variables(t_var *v, char *str)
{
	v->copy = ft_substr(str, 1, 250);
	v->len = ft_strlen(v->copy);
	v->i = -1;
}

void	variable_assigner(t_chars *x)
{
	x->line = readline("> ");
	x->temp = ft_strdup(x->line);
	x->i = 0;
}

void	looper(t_var *v, char **str)
{
	*str = NULL;
	v->j = 0;
	while (g_mini.env[v->i][v->j] != '\0' && g_mini.env[v->i][v->j] != '=')
		v->j++;
	*str = ft_substr(g_mini.env[v->i], v->j + 1, 250);
}

char	*replace_var(char *str)
{
	t_var	v;

	assign_variables(&v, str);
	if (v.len == 1)
	{
		while (g_mini.env[++v.i])
			if (v.copy[0] == g_mini.env[v.i][0] && (g_mini.env[v.i][1] == '=' \
			|| g_mini.env[v.i][1] == '\0'))
				break ;
	}
	else
	{
		while (g_mini.env[++v.i])
			if (ft_strncmp(v.copy, g_mini.env[v.i], v.len - 1) == 0)
				break ;
	}
	if (g_mini.env[v.i] == NULL)
		return (NULL);
	if (ft_strncmp(v.copy, g_mini.env[v.i], v.len - 1) == 0)
		looper(&v, &str);
	else
		null_stringer(&str);
	return (str);
}

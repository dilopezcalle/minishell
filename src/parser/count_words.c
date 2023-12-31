/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:46:53 by almirand          #+#    #+#             */
/*   Updated: 2022/10/13 15:11:43 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "structs.h"

int	error_syntax(void);

static void	quote_error(int quote, char c, int	*n_words)
{
	if (c == '\0' && quote != 0)
	{
		g_exit_status = 1;
		printf("minishell: syntax error, quotes not closed.\n");
		*n_words = -1;
	}
}

int	is_equals(char c, char	*chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		if (chars[i++] == c)
			return (1);
	}
	return (0);
}

static void	treat_quote(int	*i, int	*n_words, char	*s)
{
	int	quote;

	quote = 0;
	while (s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			quote = s[(*i)++];
			while (s[*i] != quote && s[*i])
				(*i)++;
			if (s[*i] == quote)
			{
				quote = 0;
				(*i)++;
			}
		}
		if (is_equals(s[*i], "| <>") == 1)
			break ;
		while (is_equals(s[*i], "<> |'\"") == 0 && s[*i])
			(*i)++;
	}
	quote_error(quote, s[*i], n_words);
}

void	add_var(int	*i, int	*n_words)
{
	(*i)++;
	(*n_words)++;
}

int	treat_split(int	*i, int	*n_words, char	*s)
{
	while (s[*i] != ' ' && s[*i] != '\'' && s[*i] != '"' && s[*i])
	{
		if (s[*i] == '<' || s[*i] == '>')
		{
			(*n_words)++;
			(*i)++;
			if (s[*i] == s[(*i) - 1])
				(*i)++;
			if (is_equals(s[*i], " \"'|") == 0 && s[*i] != '\0')
				add_var(i, n_words);
		}
		else if (s[(*i)++] == '|')
		{
			if (s[(*i)] == '|')
				return (error_syntax());
			(*n_words)++;
			if (s[*i] != ' ' && s[*i] != '<' && s[*i] != '>' && s[*i] != '\0')
				(*n_words)++;
			break ;
		}
	}
	treat_quote(i, n_words, s);
	return (0);
}

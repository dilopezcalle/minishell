/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:12 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/28 11:39:21 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "libft.h"
#include <readline/readline.h>

t_command	*parser(char *command_line);
char		**lexer(char *command_line);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);

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
		if (s[*i] == ' ' || s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
			break ;
		while (s[*i] != ' ' && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && s[*i] != '"' && s[*i] != '\'' && s[*i])
			(*i)++;
	}
	if (s[*i] == '\0' && quote != 0)
		*n_words = -1;
}

static void	treat_split(int	*i, int	*n_words, char	*s)
{
	while (s[*i] != ' ' && s[*i] != '\'' && s[*i] != '"' && s[*i])
	{
		if (s[*i] == '<' || s[*i] == '>')
		{
			(*n_words)++;
			(*i)++;
			if (s[*i] == s[(*i) - 1])
				(*i)++;
			else if (s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' && s[*i] != '|' && s[*i] != '\0')
			{
				(*i)++;
				(*n_words)++;
			}
		}
		else if (s[(*i)++] == '|')
		{
			(*n_words)++;
			if (s[*i] != ' ' && s[*i] != '<' && s[*i] != '>' && s[*i] != '\0')
				(*n_words)++;
			break ;
		}
	}
	treat_quote(i, n_words, s);
}

static int	ft_countwords(char	*s)
{
	int		n_words;
	int		i;

	i = 0;
	n_words = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] != '\0' && s[i] != '<' && s[i] != '>' && s[i] != '|')
			n_words++;
		treat_split(&i, &n_words, s);
	}
	return (n_words);
}

char	**tokenize(char	*line, int n_words)
{
	char	**token;
	int		i;
	int		j;
	int		start;
	int		size;
	int		c;
	int		quote;

	i = -1;
	j = 0;
	start = -1;
	size = ft_strlen(line);
	quote = 0;
	token = (char **) malloc((n_words + 1) * sizeof(char *));
	if (!token || sizeof(token) == 0)
		return (NULL);
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '|' && line[i] != '<' && line[i] != '>' && start < 0)
			start = i;
		if ((line[i] == '"' || line[i] == '\'') && quote == 0)
			quote = line[i];
		else if (quote == line[i])
			quote = 0;
		if (start >= 0 && quote == 0 &&(line[i + 1] == ' ' || line[i + 1] == '|' || line[i + 1] == '<' || line[i + 1] == '>' || i + 1 == size)) //quitar line[i]
		{
			token[j++] = ft_substr(line, start, i - start + 1);
			start = -1;
		}
		if (line[i] == '|' && quote == 0)
			token[j++] = ft_substr(line, i, 1);
		else if ((line[i] == '<' || line[i] == '>') && quote == 0)
		{
			c = line[i];
			if (line[i + 1] == c)
				token[j++] = ft_substr(line, i++, 2);
			else
				token[j++] = ft_substr(line, i, 1);
		}
		//WIP: una palabra o un pipe dan new line, problemas basura con clean_expand, hola$USER@, $? $$ $_
	}
	token[j] = NULL;
	return (token);
}

int	ft_isvalidchar(int c)
{
	if (c == '_' || (c >= '0' && c <= '9')
		|| ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
		return (1);
	return (0);
}

int	len_expand(char	*token, int *i)
{
	int		start;
	char	*substr;
	int		size;

	start = *i;
	/* if (token[*i] == '?')
	else if (token[*i] == '$')
	else if (token[*i] == '_') */
	while (token[*i] && ft_isvalidchar(token[*i]))
		(*i)++;
	substr = ft_substr(token, start, *i - start);
	size = ft_strlen(getenv(substr));
	free (substr);
	return (size);
}

int	ft_lenresize(char	*token)
{
	int	i;
	int	quote;
	int	len;

	i = 0;
	quote = 0;
	len = 0;
	while (token[i])
	{
		if (token[i] == '$' && quote != '\'')
		{
			i++;
			len += len_expand(token, &i);
		}
		else if (token[i] == '"' || token[i] == '\'')
		{
			if (quote == 0)
				quote = token[i];
			else if (quote == token[i])
				quote = 0;
			else
				len++;
			i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*ft_free_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = malloc (len_s1 + len_s2 + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, len_s1 + 1);
	ft_strlcat(join, s2, len_s2 + len_s1 + 1);
	free(s1);
	free(s2);
	return (join);
}

char	*clean(char	*token)
{
	int		i;
	char	*new_token;
	int		start;
	int		quote;
	char	*aux;
	char	*aux2;
	int		size;

	i = 0;
	size = ft_lenresize(token);
	quote = 0;
	new_token = (char *) calloc((size + 1), sizeof(char));
	if (size == 0)
	{
		ft_strlcpy(new_token, "", 1);
		return (new_token);
	}
	start = -1;
	while (token[i])
	{
		if (start == -1)
			start = i;
		if ((token[i] == '"' || token[i] == '\'') && quote == 0)
		{
			quote = token[i];
			if (start != i)
				new_token = ft_free_strjoin(new_token, ft_substr(token, start, i - start));
			start = ++i;
		}
		else if (token[i] == quote)
		{
			quote = 0;
			new_token = ft_free_strjoin(new_token, ft_substr(token, start, i - start));
			start = ++i;
		}
		else if (token[i] == '$' && quote != '\'')
		{
			if (start != i)
				new_token = ft_free_strjoin(new_token, ft_substr(token, start, i - start));
			start = ++i;
			if (token[i] == '?')
				printf("ERROR STATUS\n"); //ft_strdup(ft_itoa(g_status))
			else if (token[i] == '_')
				printf("LAST COMMAND\n");
			else if (token[i] == '$')
				printf("PID\n"); //ft_strdup(ft_itoa(pid))
			else
			{
				while (token[i] && ft_isvalidchar(token[i]))
					i++;
				aux = ft_substr(token, start, i - start);
				aux2 = new_token;
				new_token = ft_strjoin(aux2, getenv(aux));
				free(aux);
				free(aux2);
				start = i;
			}
		}
		else
			i++;
	}
	if (start != i)
		new_token = ft_free_strjoin(new_token, ft_substr(token, start, i - start));
	return (new_token);
}

char	**clean_expand(int words, char	**token)
{
	int		i;
	char	**new_token;

	i = 0;
	new_token = (char **) calloc((words + 1), sizeof(char *));
	new_token[words] = NULL;
	while (i < words)
	{
		new_token[i] = clean(token[i]);
		free(token[i++]);
	}
	free(token);
	return (new_token);
}

char	**tokens(char *line)
{
	int		words;
	char	**token;
	char	*prompt;
	int		i;

	words = ft_countwords(line);
	if (words == -1)
	{
		printf("syntax error\n");
		return (NULL);
	}
	token = clean_expand(words, tokenize(line, words));
	if (!token)
		return (free(token), NULL);
	return (token);
}

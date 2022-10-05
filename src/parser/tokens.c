/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:12 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/05 18:35:22 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "libft.h"
#include "ft_getenv.h"
#include <readline/readline.h>

t_command	*parser(char *command_line);
char		**lexer(char *command_line);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
char		*ft_getenv(char	*var, char	**envp);
int			join_home_folder(char **str_dir, char **envp);

static void	quote_error(int quote, char	c, int	*n_words)
{
	if (c == '\0' && quote != 0)
	{
		printf("minishell: syntax error, quotes not closed.\n");
		*n_words = -1;
	}
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
		if (s[*i] == ' ' || s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
			break ;
		while (s[*i] != ' ' && s[*i] != '<' && s[*i] != '>' && s[*i] != '|' && s[*i] != '"' && s[*i] != '\'' && s[*i]) // FUNCION
			(*i)++;
	}
	quote_error(quote, s[*i], n_words);
}

static int	treat_split(int	*i, int	*n_words, char	*s)
{
	while (s[*i] != ' ' && s[*i] != '\'' && s[*i] != '"' && s[*i])
	{
		if (s[*i] == '<' || s[*i] == '>')
		{
			(*n_words)++;
			(*i)++;
			if (s[*i] == s[(*i) - 1])
				(*i)++;
			else if (s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' && s[*i] != '|' && s[*i] != '\0') //FUNCION
			{
				(*i)++;
				(*n_words)++;
			}
		}
		else if (s[(*i)++] == '|')
		{
			if (s[(*i)] == '|')
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (-1);
			}
			(*n_words)++;
			if (s[*i] != ' ' && s[*i] != '<' && s[*i] != '>' && s[*i] != '\0')
				(*n_words)++;
			break ;
		}
	}
	treat_quote(i, n_words, s);
	return (0);
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
		if (treat_split(&i, &n_words, s) == -1)
			return (-1);
	}
	return (n_words);
}

static void	redirect(char	*line, char	***token, int	*i, int	*j)
{
	int	c;

	c = line[*i];
	if (line[(*i) + 1] == c)
		(*token)[(*j)++] = ft_substr(line, (*i)++, 2);
	else
		(*token)[(*j)++] = ft_substr(line, *i, 1);
}

static void	init_tokenize(int *i, int *j, int	*start, int	*quote)
{
	*i = -1;
	*j = 0;
	*start = -1;
	*quote = 0;
}

static void	tokenize_quote(int	*start, int	*quote, char c, int i)
{
	if (c != ' ' && c != '|' && c != '<' && c != '>' && *start < 0)
		*start = i;
	if ((c == '"' || c == '\'') && *quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

char	**tokenize(char	*line, int n_words)
{
	char	**token;
	int		i;
	int		j;
	int		start;
	int		quote;

	init_tokenize(&i, &j, &start, &quote);
	token = (char **) malloc((n_words + 1) * sizeof(char *));
	if (!token || sizeof(token) == 0)
		return (NULL);
	while (line[++i])
	{
		tokenize_quote(&start, &quote, line[i], i);
		if (start >= 0 && quote == 0 && (line[i + 1] == ' ' || line[i + 1] == '|' || line[i + 1] == '<' || line[i + 1] == '>' || i + 1 == ft_strlen(line)))
		{
			token[j++] = ft_substr(line, start, i - start + 1);
			start = -1;
		}
		if (line[i] == '|' && quote == 0)
			token[j++] = ft_substr(line, i, 1);
		else if ((line[i] == '<' || line[i] == '>') && quote == 0)
			redirect(line, &token, &i, &j);
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

int	len_expand(char	*token, int *i, char	**envp)
{
	int		start;
	char	*substr;
	int		size;
	char	*getenv;

	start = *i;
	if (token[*i] == '?')
		return (1);
	while (token[*i] && ft_isvalidchar(token[*i]))
		(*i)++;
	substr = ft_substr(token, start, *i - start);
	getenv = ft_getenv(substr, envp);
	size = ft_strlen(getenv);
	free (substr);
	free (getenv);
	return (size);
}

int	get_virgulilla_size(char **envp)
{
	char	*home;
	int		len;

	home = ft_getenv("HOME", envp);
	len = ft_strlen(home);
	if (home)
		free(home);
	return (len);
}

static void	dollar(char	*token, char	**envp, int	*i, int	*len)
{
	(*i)++;
	while (token[*i] == '$')
	{
		(*i)++;
		(*len)++;
	}
	if (token[*i] != '\0' && token[*i] != ' ')
		(*len) += len_expand(token, i, envp);
}

static void	quote_len(int *quote, char token, int	*len)
{
	if (quote == 0)
		*quote = token;
	else if (*quote == token)
		*quote = 0;
	else
		(*len)++;
}

int	ft_lenresize(char	*token, char	**envp)
{
	int	i;
	int	quote;
	int	len;

	i = 0;
	quote = 0;
	len = 0;
	while (token[i])
	{
		if (token[i] == '$' && quote != '\'' && token[i + 1] != '\0')
			dollar(token, envp, &i, &len);
		else if (quote != '\'' && quote != '"' && (i == 0 && token[i] == '~' && (token[i + 1] == '\0' || token[i + 1] == '/'))) //FUNCION
		{
			len += get_virgulilla_size(envp);
			i++;
		}
		else if (token[i] == '"' || token[i] == '\'')
			quote_len(&quote, token[i++], &len);
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*free_join(char *s1, char *s2)
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

char	*clean(char	*token, char **envp)
{
	int		i;
	char	*new_token;
	int		start;
	int		quote;
	char	*aux;
	int		size;

	i = 0;
	size = ft_lenresize(token, envp);
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
				new_token = free_join(new_token, ft_substr(token, start, i - start));
			start = ++i;
		}
		else if (token[i] == quote)
		{
			quote = 0;
			new_token = free_join(new_token, ft_substr(token, start, i - start));
			start = ++i;
		}
		else if (token[i] == '$' && quote != '\'' && token[i + 1] != '\0')
		{
			while (token[i] == '$')
				i++;
			if (start != i && token[i + 1] != '\0')
				new_token = free_join(new_token, ft_substr(token, start, i - start - 1));
			else if (start != i && token[i + 1] == '\0')
				new_token = free_join(new_token, ft_substr(token, start, i - start));
			start = i;
			if (token[i] == '?')
			{
				new_token = ft_itoa(g_exit_status);
				i++;
			}
			else
			{
				while (token[i] && ft_isvalidchar(token[i]))
					i++;
				aux = ft_substr(token, start, i - start);
				if (ft_getenv(aux, envp))
					new_token = free_join(new_token, ft_getenv(aux, envp));
				free(aux);
			}
			start = i;
		}
		else if (quote != '\'' && quote != '"' && (i == 0 && token[i] == '~' && (token[i + 1] == '\0' || token[i + 1] == '/')))
		{
			if (join_home_folder(&new_token, envp))
				return (0);
			start = ++i;
		}
		else
			i++;
	}
	if (start != i)
		new_token = free_join(new_token, ft_substr(token, start, i - start));
	return (new_token);
}

char	**clean_expand(int words, char	**token, char	**envp)
{
	int		i;
	char	**new_token;

	i = 0;
	new_token = (char **) calloc((words + 1), sizeof(char *));
	new_token[words] = NULL;
	while (i < words)
	{
		new_token[i] = clean(token[i], envp);
		free(token[i++]);
	}
	free(token);
	return (new_token);
}

char	**tokens(char *line, char	**envp)
{
	int		words;
	char	**token;

	words = ft_countwords(line);
	if (words == -1)
		return (NULL);
	token = clean_expand(words, tokenize(line, words), envp);
	return (token);
}

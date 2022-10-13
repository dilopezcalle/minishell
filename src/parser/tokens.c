/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:51:12 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/13 15:12:22 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "ft_getenv.h"
#include <readline/readline.h>
#include "tokens.h"

t_command	*parser(char *command_line);
char		**lexer(char *command_line);
char		*ft_getenv(char	*var, char	**envp);
int			join_home_folder(char **str_dir, char **envp);

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

char	**tokenize(char	*line, int n_words)
{
	char	**token;
	int		i;
	int		j;
	int		start;
	int		quote;

	init_tokenize(&i, &j, &start, &quote);
	token = (char **) ft_calloc((n_words + 1), sizeof(char *));
	if (!token)
		return (token);
	while (line[++i] && tokenize_quote(&start, &quote, line[i], i))
	{
		if (line[i] == '|' && quote == 0)
			token[j++] = ft_substr(line, i, 1);
		else if ((line[i] == '<' || line[i] == '>') && quote == 0)
			redirect(line, &token, &i, &j);
		else if ((start >= 0 && quote == 0 && is_equals(line[i + 1], " |<>"))
			|| i + 1 == (int)ft_strlen(line))
		{
			token[j++] = ft_substr(line, start, i - start + 1);
			start = -1;
		}
	}
	token[j] = NULL;
	return (token);
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
		else if (quote != '\'' && quote != '"' && (i == 0 && token[i] == '~' \
				&& (token[i + 1] == '\0' || token[i + 1] == '/')))
		{
			len += get_virgulilla_size(envp);
			i++;
		}
		else if (token[i] == '"' || token[i] == '\'')
			quote_len(&quote, token[i++], &len);
		else if (i++ >= 0)
			len++;
	}
	return (len);
}

t_token	*clean_expand(int words, char	**token, char	**envp)
{
	int		i;
	t_token	*ar_token;

	i = 0;
	ar_token = (t_token *)ft_calloc(words + 1, sizeof(t_token));
	while (i < words)
	{
		ar_token[i] = clean(token[i], envp);
		free(token[i++]);
	}
	free(token);
	ar_token[i].str = 0;
	return (ar_token);
}

t_token	*tokens(char *line, char **envp)
{
	int		words;
	t_token	*ar_token;

	words = ft_countwords(line);
	if (words == -1)
	{
		if (g_exit_status != 1)
			g_exit_status = 258;
		return (NULL);
	}
	ar_token = clean_expand(words, tokenize(line, words), envp);
	return (ar_token);
}

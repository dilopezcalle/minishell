/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:23:58 by almirand          #+#    #+#             */
/*   Updated: 2022/10/13 16:17:09 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "libft.h"
#include "lexer.h"

void	redirect(char	*line, char	***token, int	*i, int	*j)
{
	int	c;

	c = line[*i];
	if (line[(*i) + 1] == c)
		(*token)[(*j)++] = ft_substr(line, (*i)++, 2);
	else
		(*token)[(*j)++] = ft_substr(line, *i, 1);
}

void	init_tokenize(int *i, int *j, int *start, int *quote)
{
	*i = -1;
	*j = 0;
	*start = -1;
	*quote = 0;
}

int	tokenize_quote(int	*start, int	*quote, char c, int i)
{
	if (c != ' ' && c != '|' && c != '<' && c != '>' && *start < 0)
		*start = i;
	if ((c == '"' || c == '\'') && *quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
	return (1);
}

t_command	*malloc_commands(t_token **ar_token, char **command_args)
{
	int			num_command;
	t_command	*commands;
	int			i;

	num_command = 1;
	i = -1;
	while (command_args[++i])
		if (!(*ar_token)[i].quote[0] && command_args[i][0] == '|')
			num_command++;
	commands = (t_command *) ft_calloc(1, sizeof(t_command));
	if (!commands)
		return (free_ar_token(ar_token), NULL);
	commands->simple_commands = (t_simple_command **) \
					ft_calloc((num_command + 1), sizeof(t_simple_command *));
	if (!commands->simple_commands)
		return (free_ar_token(ar_token), NULL);
	return (commands);
}

void	create_first_argument(t_simple_command *command, char *arg)
{
	command->arguments = (char **)ft_calloc(2, sizeof(char *));
	command->arguments[0] = ft_strdup(arg);
	command->number_arguments = 1;
}

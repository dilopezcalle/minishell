/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:34:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/13 17:01:24 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

#include "signals.h"
#include "tokens.h"
#include "lexer.h"
#include "libft.h"

t_token	*lexer(char *command_line, char	**envp)
{
	t_token	*ar_token;
	int		i;

	i = 0;
	ar_token = tokens(command_line, envp);
	if (!ar_token)
		ar_token = (t_token *)ft_calloc(1, sizeof(t_token));
	else if (ar_token->str && ar_token->str[0] == '\0')
	{
		free(ar_token->str);
		ar_token->str = NULL;
	}
	free(command_line);
	return (ar_token);
}

void	free_ar_token(t_token **ar_token)
{
	int	i;

	i = 0;
	while ((*ar_token)[i].str)
	{
		free((*ar_token)[i].quote);
		i++;
	}
	free(*ar_token);
}

void	dub_stdin_infile_2(int fd_pipe[2], t_simple_command *command)
{
	signal(SIGINT, sig_handler_without_input);
	signal(SIGQUIT, sig_handler_heredoc);
	close(fd_pipe[1]);
	wait(NULL);
	command->infile = fd_pipe[0];
}

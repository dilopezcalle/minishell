/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:34:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 11:47:15 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Separar en "argumentos" los comandos con sus argumentos, el input y el output
t_token	*lexer(char *command_line, char	**envp)
{
	t_token	*ar_token;
	int		i;

	ar_token = tokens(command_line, envp);
	if (ar_token->str && ar_token->str[0] == '\0')
	{
		free(ar_token->str);
		ar_token->str = NULL;
	}
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

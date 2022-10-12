/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:34:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 18:31:37 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

#include "lexer.h"
#include "libft.h"
#include "tokens.h"

// Separar en "argumentos" los comandos con sus argumentos, el input y el output
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

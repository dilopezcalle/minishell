/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:34:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/07 15:31:55 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Separar en "argumentos" los comandos con sus argumentos, el input y el output
t_token	*lexer(char *command_line, char	**envp)
{
	t_token	*ar_token;
	int		i;

	ar_token = tokens(command_line, envp);
	// i = 0;
	// if (ar_token[i].str)
	// {
	// 	printf("%s\n", ar_token[i].str);
	// 	i++;
	// }
	if (ar_token && ar_token[0].str)
		printf("llega %d\n", ar_token[0].len);
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

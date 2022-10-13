/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:02:41 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/13 14:48:56 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "syntax_errors.h"

// Comprueba que existan cosas luego de un >, < ó |
int	check_syntax_errors(char **separate, t_token *ar_token)
{
	int	i;

	i = 1;
	if (separate[0][0] == '|')
		return (print_syntax_error(separate[i - 1]));
	while (separate[i])
	{
		if (separate[i][1] && !ar_token[i].quote[0] && ((separate[i][0] == '>' && separate[i][1] != '>') \
			|| (separate[i][0] == '<' && separate[i][1] != '<')))
			return (print_syntax_error(separate[i] + 1));
		if (!ar_token[i].quote[0] && !ar_token[i - 1].quote[0] && (separate[i][0] == '>' || separate[i][0] == '<' \
			|| separate[i][0] == '|') && (separate[i - 1][0] == '>' \
			|| separate[i - 1][0] == '<'))
			return (print_syntax_error(separate[i]));
		i++;
	}
	if (i > 0 && !ar_token[i - 1].quote[0] && (separate[i - 1][0] == '>' || separate[i - 1][0] == '<' \
		|| separate[i - 1][0] == '|'))
		return (print_syntax_error(separate[i - 1]));
	return (0);
}

// Printea error de sintáxis
int	print_syntax_error(char *str)
{
	g_exit_status = 258;
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (1);
}

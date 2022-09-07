/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 11:02:41 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/04 13:19:21 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	print_syntax_error(char *str);

int	check_syntax_errors(char **separate)
{
	int	i;

	i = 1;
	while (separate[i])
	{
		if (separate[i][1] && ((separate[i][0] == '>' && separate[i][1] != '>') \
			|| (separate[i][0] == '<' && separate[i][1] != '<')))
			return (print_syntax_error(separate[i] + 1));
		if ((separate[i][0] == '>' || separate[i][0] == '<' \
			|| separate[i][0] == '|') && (separate[i - 1][0] == '>' \
			|| separate[i - 1][0] == '<'))
			return (print_syntax_error(separate[i]));
		i++;
	}
	if (i > 0 && (separate[i - 1][0] == '>' || separate[i - 1][0] == '<' \
		|| separate[i - 1][0] == '|'))
		return (print_syntax_error(separate[i - 1]));
	return (0);
}

static int	print_syntax_error(char *str)
{
	printf("ERROR \'%s\'\n", str);
	return (1);
}

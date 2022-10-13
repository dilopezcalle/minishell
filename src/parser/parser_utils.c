/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:23:58 by almirand          #+#    #+#             */
/*   Updated: 2022/10/13 11:26:31 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	redirect(char	*line, char	***token, int	*i, int	*j)
{
	int	c;

	c = line[*i];
	if (line[(*i) + 1] == c)
		(*token)[(*j)++] = ft_substr(line, (*i)++, 2);
	else
		(*token)[(*j)++] = ft_substr(line, *i, 1);
}

void	init_tokenize(int *i, int *j, int	*start, int	*quote)
{
	*i = -1;
	*j = 0;
	*start = -1;
	*quote = 0;
}

void	tokenize_quote(int	*start, int	*quote, char c, int i)
{
	if (c != ' ' && c != '|' && c != '<' && c != '>' && *start < 0)
		*start = i;
	if ((c == '"' || c == '\'') && *quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

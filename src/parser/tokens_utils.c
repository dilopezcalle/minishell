/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:14:16 by almirand          #+#    #+#             */
/*   Updated: 2022/10/13 11:18:11 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char	*var, char	**envp);

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

void	dollar(char	*token, char	**envp, int	*i, int	*len)
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

void	quote_len(int *quote, char token, int	*len)
{
	if (quote == 0)
		*quote = token;
	else if (*quote == token)
		*quote = 0;
	else
		(*len)++;
}

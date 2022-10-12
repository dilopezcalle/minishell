/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:41:51 by almirand          #+#    #+#             */
/*   Updated: 2022/10/12 15:46:13 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"

char	*ft_getenv(char	*var, char	**envp);
int		ft_isvalidchar(int c);

void	clean_expand1(char	*token, int	*i, int	*start, char	**new_token)
{
	int	len;

	while (token[*i] == '$')
		(*i)++;
	len = (*i) - (*start);
	if (*start != *i && (token[*i] == '\0'
			|| (ft_isvalidchar(token[*i]) == 0 && token[*i] != '?')))
		*new_token = free_join(*new_token, ft_substr(token, *start, len));
	else if (*start != *i && token[*i] != '\0')
		*new_token = free_join(*new_token, ft_substr(token, *start, len - 1));
	*start = *i;
}

int	clean_expand2(char	*token, int	*i, char	**envp, char	**new_token)
{
	int		start;
	char	*aux;
	char	*env;

	start = *i;
	if (token[*i] == '?')
	{
		*new_token = free_join(*new_token, ft_itoa(g_exit_status));
		(*i)++;
	}
	else
	{
		while (token[*i] && ft_isvalidchar(token[*i]))
			(*i)++;
		aux = ft_substr(token, start, (*i) - start);
		env = ft_getenv(aux, envp);
		if (env)
			*new_token = free_join(*new_token, env);
		free(aux);
	}
	return (*i);
}

int	quotize1(int	*start, char	*token, int	*i, char	**new_token)
{
	int	len;

	len = (*i) - (*start);
	if (*start != *i)
		*new_token = free_join(*new_token, ft_substr(token, *start, len));
	*start = ++(*i);
	return (token[(*i) - 1]);
}

int	quotize2(int	*start, char	*token, int	*i, char	**new_token)
{
	*new_token = free_join(*new_token, ft_substr(token, *start, *i - *start));
	*start = ++(*i);
	return (0);
}

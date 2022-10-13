/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:41:51 by almirand          #+#    #+#             */
/*   Updated: 2022/10/13 11:08:30 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"

char	*ft_getenv(char	*var, char	**envp);
int		ft_isvalidchar(int c);

void	clean_expand1(char	*token, t_clean *cl)
{
	int	len;

	while (token[(*cl).i] == '$')
		((*cl).i)++;
	len = ((*cl).i) - ((*cl).start);
	if ((*cl).start != (*cl).i && (token[(*cl).i] == '\0'
			|| (ft_isvalidchar(token[(*cl).i]) == 0 && token[(*cl).i] != '?')))
		(*cl).new_token = free_join((*cl).new_token, \
				ft_substr(token, (*cl).start, len));
	else if ((*cl).start != (*cl).i && token[(*cl).i] != '\0')
		(*cl).new_token = free_join((*cl).new_token, \
				ft_substr(token, (*cl).start, len - 1));
	(*cl).start = (*cl).i;
}

int	clean_expand2(char	*token, t_clean *cl, char	**envp)
{
	int		start;
	char	*aux;
	char	*env;

	start = (*cl).i;
	if (token[(*cl).i] == '?')
	{
		(*cl).new_token = free_join((*cl).new_token, ft_itoa(g_exit_status));
		((*cl).i)++;
	}
	else
	{
		while (token[(*cl).i] && ft_isvalidchar(token[(*cl).i]))
			((*cl).i)++;
		aux = ft_substr(token, start, ((*cl).i) - start);
		env = ft_getenv(aux, envp);
		if (env)
			(*cl).new_token = free_join((*cl).new_token, env);
		free(aux);
	}
	return ((*cl).i);
}

int	quotize1(t_clean	*cl, char	*token)
{
	int	len;

	len = (*cl).i - (*cl).start;
	if ((*cl).start != (*cl).i)
		(*cl).new_token = free_join((*cl).new_token, \
				ft_substr(token, (*cl).start, len));
	(*cl).start = ++((*cl).i);
	return (token[((*cl).i) - 1]);
}

int	quotize2(t_clean	*cl, char	*token)
{
	(*cl).new_token = free_join((*cl).new_token, \
			ft_substr(token, (*cl).start, (*cl).i - (*cl).start));
	(*cl).start = ++((*cl).i);
	return (0);
}

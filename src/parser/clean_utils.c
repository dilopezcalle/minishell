/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:18:45 by almirand          #+#    #+#             */
/*   Updated: 2022/10/13 12:18:37 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "clean_utils.h"
#include "libft.h"
#include "utils.h"

int	error_syntax(void)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	return (-1);
}

t_clean	init_clean(t_clean s_clean, char	*token, char	**envp)
{
	s_clean.i = 0;
	s_clean.size = ft_lenresize(token, envp);
	s_clean.quote = 0;
	s_clean.index = 0;
	s_clean.new_token = (char *) ft_calloc((s_clean.size + 1), sizeof(char));
	s_clean.s_token.quote = (int *) ft_calloc(s_clean.size, sizeof(int));
	s_clean.s_token.len = 0;
	s_clean.start = -1;
	return (s_clean);
}

void	clean_1(t_clean *cl, char	*token, char	**envp)
{
	if ((token[(*cl).i] == '"' || token[(*cl).i] == '\'') && (*cl).quote == 0)
		(*cl).quote = quotize1(cl, token);
	else if (token[(*cl).i] == (*cl).quote)
		(*cl).quote = quotize2(cl, token);
	else if (token[(*cl).i] == '$' && (*cl).quote != '\''
		&& token[(*cl).i + 1] != '\0')
	{
		clean_expand1(token, cl);
		(*cl).start = clean_expand2(token, cl, envp);
	}
	else if ((*cl).quote != '\'' && (*cl).quote != '"' && ((*cl).i == 0 \
			&& token[(*cl).i] == '~' && (token[(*cl).i + 1] == '\0'
				|| token[(*cl).i + 1] == '/')))
	{
		if (join_home_folder(&((*cl).new_token), envp))
		{
			(*cl).s_token.str = (*cl).new_token;
			//return ((*cl).s_token);
		}
		(*cl).start = ++((*cl).i);
	}
	else
		(*cl).i++;
}

void	clean_loop(t_clean *cl, char	*token, char	**envp)
{
	while (token[(*cl).i])
	{
		if (token[(*cl).i] != '\'' && token[(*cl).i] != '"')
		{
			if (token[(*cl).i] != (*cl).quote)
			{
				(*cl).s_token.quote[(*cl).index] = (*cl).quote;
				(*cl).index++;
			}
			(*cl).s_token.len++;
		}
		if ((*cl).start == -1)
			(*cl).start = (*cl).i;
		clean_1(cl, token, envp);
	}
}

t_token	clean(char	*token, char **envp)
{
	t_clean	cl;

	cl = init_clean(cl, token, envp);
	if (cl.size == 0)
	{
		ft_strlcpy(cl.new_token, "", 1);
		cl.s_token.str = cl.new_token;
		return (cl.s_token);
	}
	clean_loop(&cl, token, envp);
	if (cl.start != cl.i)
		cl.new_token = free_join(cl.new_token,
				ft_substr(token, cl.start, cl.i - cl.start));
	cl.s_token.str = cl.new_token;
	if (cl.s_token.len == 0)
		cl.s_token.len = 1;
	return (cl.s_token);
}

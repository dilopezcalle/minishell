/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:44:26 by almirand          #+#    #+#             */
/*   Updated: 2022/10/12 18:31:02 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "structs.h"

void	clean_expand1(char	*token, int	*i, int	*start, char	**new_token);
int		clean_expand2(char	*token, int	*i, char	**envp, char	**new_token);
int		quotize1(int	*start, char	*token, int	*i, char	**new_token);
int		quotize2(int	*start, char	*token, int	*i, char	**new_token);
int		treat_split(int	*i, int	*n_words, char	*s);
int		is_equals(char c, char	*chars);
t_token	*tokens(char *line, char **envp);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:44:26 by almirand          #+#    #+#             */
/*   Updated: 2022/10/13 11:55:12 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "structs.h"

t_token	clean(char	*token, char **envp);
int		treat_split(int	*i, int	*n_words, char	*s);
int		is_equals(char c, char	*chars);
t_token	*tokens(char *line, char **envp);
int		ft_isvalidchar(int c);
int		len_expand(char	*token, int *i, char	**envp);
int		get_virgulilla_size(char **envp);
void	dollar(char	*token, char	**envp, int	*i, int	*len);
void	quote_len(int *quote, char token, int	*len);
void	tokenize_quote(int	*start, int	*quote, char c, int i);
void	init_tokenize(int *i, int *j, int	*start, int	*quote);
void	redirect(char	*line, char	***token, int	*i, int	*j);

#endif

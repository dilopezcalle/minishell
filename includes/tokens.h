/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:44:26 by almirand          #+#    #+#             */
/*   Updated: 2022/10/08 11:56:02 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

void	clean_expand1(char	*token, int	*i, int	*start, char	**new_token);
int		clean_expand2(char	*token, int	*i, char	**envp, char	**new_token);
int		quotize1(int	*start, char	*token, int	*i, char	**new_token);
int		quotize2(int	*start, char	*token, int	*i, char	**new_token);
int		treat_split(int	*i, int	*n_words, char	*s);
int		is_equals(char c, char	*chars);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:19:52 by almirand          #+#    #+#             */
/*   Updated: 2022/10/13 11:32:31 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_UTILS_H
# define CLEAN_UTILS_H

int		ft_lenresize(char	*token, char	**envp);
void	clean_expand1(char	*token, t_clean *cl);
int		clean_expand2(char	*token, t_clean *cl, char	**envp);
int		quotize1(t_clean	*cl, char	*token);
int		quotize2(t_clean	*cl, char	*token);

#endif

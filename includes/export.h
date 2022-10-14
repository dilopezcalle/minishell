/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:31:22 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/14 19:00:51 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

int		export_builtin(char **commands, char ***envp);
int		export_builtin1(char *var, char ***envp);
int		ft_str_isalnum(char	*str);
void	error_invalid_id(char *c);

#endif

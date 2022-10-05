/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:00:42 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/05 16:21:03 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CHILD_H
# define BUILTIN_CHILD_H

# include "structs.h"
# include "libft.h"

void	echo_builtin(t_simple_command *command);
int		pwd_builtin(t_simple_command *command);
void	env_builtin(char **envp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:00:42 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 17:06:41 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CHILD_H
# define BUILTIN_CHILD_H

# include "structs.h"

int	execute_child_builtin(t_simple_command *command, char **envp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:00:42 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 17:07:18 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_PARENT_H
# define BUILTIN_PARENT_H

# include "structs.h"

int	execute_parent_builtin(t_simple_command *command, char **envp[]);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:20:55 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/14 13:05:55 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_parent.h"
#include "libft.h"
#include "unset.h"
#include "export.h"
#include "cd.h"

int	execute_parent_builtin(t_simple_command *command, char **envp[])
{
	if (ft_strncmp(command->arguments[0], "cd", 3) == 0)
		return (cd_builtin(command, envp));
	if (ft_strncmp(command->arguments[0], "unset", 6) == 0)
		return (unset_builtin(command->arguments, envp));
	if (ft_strncmp(command->arguments[0], "export", 7) == 0)
		return (export_builtin(command->arguments, envp));
	return (0);
}

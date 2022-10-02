/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:20:55 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 18:06:58 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_parent.h"

int		exit_builtin(t_simple_command *command);
int		unset_builtin(t_simple_command *cmd, char	***envp);

int	execute_parent_builtin(t_simple_command *command, char	**envp)
{
	if (ft_strncmp(command->arguments[0], "cd", 3) == 0)
		return (cd_builtin(command));
	if (ft_strncmp(command->arguments[0], "exit", 5) == 0)
		return (exit_builtin(command));
	if (ft_strncmp(command->arguments[0], "unset", 6) == 0)
		return (unset_builtin(command, &envp));
	return (0);
}

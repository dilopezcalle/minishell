/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:20:55 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/04 09:20:53 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_parent.h"

int		exit_builtin(t_simple_command *command);
int		unset_builtin(char	*var, char	***envp);
// int		export_builtin(char	*var, char	***envp);

int	execute_parent_builtin(t_simple_command *command, char **envp[])
{
	if (ft_strncmp(command->arguments[0], "cd", 3) == 0)
		return (cd_builtin(command, envp));
	if (ft_strncmp(command->arguments[0], "exit", 5) == 0)
		return (exit_builtin(command));
	if (ft_strncmp(command->arguments[0], "unset", 6) == 0)
		return (unset_builtin(command->arguments[1], envp));
	// if (ft_strncmp(command->arguments[0], "export", 7) == 0)
	// 	return (export_builtin(command->arguments[1], &envp));
	return (0);
}

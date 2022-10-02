/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 07:57:04 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/02 12:21:48 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_child.h"

void	env_builtin(char	**envp);

int	execute_child_builtin(t_simple_command *command, char **envp)
{
	if (ft_strncmp(command->arguments[0], "echo", 5) == 0)
		echo_builtin(command);
	// else if (ft_strncmp(command->arguments[0], "env", 6) == 0)
	// 	env_builtin(envp);
	else
		exit (0);
	envp = 0;
	return (0);
}

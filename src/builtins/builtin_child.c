/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 07:57:04 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 18:16:21 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_child.h"
#include "libft.h"
#include "echo.h"
#include "env.h"
#include "pwd.h"

int	execute_child_builtin(t_simple_command *command, char **envp)
{
	if (ft_strncmp(command->arguments[0], "echo", 5) == 0)
		echo_builtin(command);
	else if (ft_strncmp(command->arguments[0], "env", 6) == 0)
		env_builtin(envp);
	else if (ft_strncmp(command->arguments[0], "pwd", 4) == 0)
		pwd_builtin(command);
	else
		exit (0);
	envp = 0;
	return (0);
}

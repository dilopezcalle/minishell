/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 07:57:04 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/29 12:07:27 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_child.h"

int	execute_child_builtin(t_simple_command *command)
{
	if (ft_strncmp(command->arguments[0], "echo", 5) == 0)
		echo_builtin(command);
	else
		exit (0);
	return (0);
}
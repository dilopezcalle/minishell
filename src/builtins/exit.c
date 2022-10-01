/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:02:21 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 10:15:42 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

int	exit_builtin(t_simple_command *command)
{
	if (command->arguments[1])
		g_exit_status = ft_atoi(command->arguments[1]);
	else
		g_exit_status = 0;
	return (0);
}

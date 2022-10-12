/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:02:21 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 17:40:33 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "libft.h"

int	exit_builtin(t_simple_command *command)
{
	int	i;

	i = -1;
	if (command->arguments[1] && command->arguments[2])
	{
		g_exit_status = 1;
		printf("exit\nbash: exit: too many arguments\n");
		return (1);
	}
	if (command->arguments[1])
	{
		while (command->arguments[1][++i])
			if (ft_isalpha(command->arguments[1][i]))
			{
				g_exit_status = 255;
				printf("minishell: exit: %s: numeric argument required\n", \
						command->arguments[1]);
				return (0);
			}
		g_exit_status = ft_atoi(command->arguments[1]);

	}
	else
		g_exit_status = 0;
	return (0);
}


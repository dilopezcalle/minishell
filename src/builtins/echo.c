/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:25:23 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/25 14:00:05 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

int	builtin_echo(t_simple_command *command)
{
	char	*flag_n;
	int		i;

	i = 1;
	flag_n = command->arguments[1];
	if (flag_n && ft_strncmp(flag_n, "-n", 2) == 0)
		while (flag_n[i] == 'n')
			i++;
	if (flag_n && !flag_n[i])
		execute_echo(command->arguments + 2);
	else
		execute_echo(command->arguments + 1);
	if (!flag_n || (flag_n && flag_n[i] != '\0'))
		write(1, "\n", 1);
	exit(0);
	return (0);
}

int	execute_echo(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		write(1, arguments[i], ft_strlen(arguments[i]));
		if (arguments[i + 1])
			write(1, " ", 1);
		i++;
	}
	return (0);
}

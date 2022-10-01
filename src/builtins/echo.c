/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:25:23 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 17:13:06 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

int	echo_builtin(t_simple_command *command)
{
	char	*flag_n;
	int		num_arg;
	int		i;

	num_arg = 1;
	flag_n = 0;
	while (ft_strncmp(command->arguments[num_arg], "-n", 2) == 0)
	{
		i = 1;
		flag_n = command->arguments[num_arg];
		if (flag_n && ft_strncmp(flag_n, "-n", 2) == 0)
			while (flag_n[i] == 'n')
				i++;
		if (flag_n && !flag_n[i])
			num_arg++;
		else
			break ;
	}
	execute_echo(command->arguments + num_arg);
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

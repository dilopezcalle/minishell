/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:23:51 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/23 13:26:27 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// Liberar la memotia de un array doble
void	free_double_array(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	is_command_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0 \
		|| ft_strncmp(command, "cd", 3) == 0 \
		|| ft_strncmp(command, "pwd", 4) == 0 \
		|| ft_strncmp(command, "export", 7) == 0 \
		|| ft_strncmp(command, "unset", 6) == 0 \
		|| ft_strncmp(command, "env", 4) == 0 \
		|| ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

// Liberar la memoria de todos los elementos de la estructura
void	free_commands(t_command **commands_dir)
{
	int			i;
	int			num_command;
	t_command	*commands;

	i = 0;
	commands = *commands_dir;
	while ((commands->simple_commands)[i])
	{
		num_command = 0;
		if (((commands->simple_commands)[i])->arguments)
		{
			while ((((commands->simple_commands)[i])->arguments)[num_command])
			{
				free((((commands->simple_commands)[i])->arguments) \
					[num_command]);
				num_command++;
			}
			free(((commands->simple_commands)[i])->arguments);
		}
		free(((commands->simple_commands)[i])->path);
		free((commands->simple_commands)[i]);
		i++;
	}
	return (free(commands->simple_commands), free(commands));
}


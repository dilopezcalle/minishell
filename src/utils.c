/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:23:51 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/14 12:39:59 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

// Imprimir algunos datos de cada comando y free de las estructuras
void	free_commands(t_command **commands_dir)
{
	int			i;
	int			num_command;
	t_command	*commands;

	i = 0;
	commands = *commands_dir;
	while ((commands->simple_commands)[i])
	{
		// printf("\n\n");
		// printf("out: %d (%d)\nin: %d (%d)\npath: %s\n", 
		// ((commands->simple_commands)[i])->outfile, 
		// ((commands->simple_commands)[i])->redirection_outfile, 
		// ((commands->simple_commands)[i])->infile, 
		// ((commands->simple_commands)[i])->redirection_infile, 
		// ((commands->simple_commands)[i])->path);
		num_command = 0;
		if (((commands->simple_commands)[i])->arguments)
		{
			while ((((commands->simple_commands)[i])->arguments)[num_command])
			{
				// printf("arg: %s\n", 
				// (((commands->simple_commands)[i])->arguments)[num_command]);
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
	// printf("\n\n");
	return (free(commands->simple_commands), free(commands));
}

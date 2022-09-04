/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:16:19 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/04 10:23:29 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Crea la estructura general de los comandos que se utilizarán
t_command	*parser(char *command_line)
{
	t_command	*commands;
	char		**command_args;
	int			num_command;
	int			i;

	command_args = lexer(command_line);
	if (!command_args)
		return (0);
	free(command_line);
	i = -1;
	num_command = 1;
	while (command_args[++i])
		if (command_args[i][0] == '|')
			num_command++;
	commands = (t_command *) ft_calloc(1, sizeof(t_command));
	if (!commands)
		return (0);
	commands->simple_commands = (t_simple_command **) \
					ft_calloc((num_command + 1), sizeof(t_simple_command *));
	if (!commands->simple_commands)
		return (0);
	if (create_and_append_simple_command(commands, &command_args))
		return (0);
	print_commands(&commands);
	return (0);
}

// Iterar y juntar argumentos para construir la estructura
static int	create_and_append_simple_command(t_command	*commands, \
											char ***command_args_dir)
{
	int			i;
	int			num_command;
	char		**command_args;

	i = -1;
	num_command = 0;
	command_args = *command_args_dir;
	while (command_args[++i] && command_args[i][0])
	{
		if (!(commands->simple_commands)[num_command])
		{
			(commands->simple_commands)[num_command] = (t_simple_command *) \
			ft_calloc(1, sizeof(t_simple_command));
			if (!((commands->simple_commands)[num_command]))
				return (1);
		}
		if (command_args[i][0] == '|')
			num_command++;
		else if (create_simple_command(\
				&(commands->simple_commands)[num_command], command_args, i))
			return (1);
		if (command_args[i][0] == '>' || command_args[i][0] == '<')
			i++;
	}
	i = -1;
	while (command_args[++i])
		free(command_args[i]);
	free(command_args);
	return (0);
}

// Guardar datos y comprobar que se guardan correctamente
static int	create_simple_command(t_simple_command **command_info, \
								char **command_arg, int index)
{
	t_simple_command	*command;
	int					len;

	len = 0;
	if (command_arg[index] && command_arg[index + 1])
		len = ft_strlen(command_arg[index + 1]);
	command = *command_info;
	fill_simple_command(command, command_arg, index, len);
	if (!command->outfile && !command->infile && !command->arguments)
		return (1);
	return (0);
}

// Guardar outfile, infile o comando en la estructura
static void	fill_simple_command(t_simple_command *command, \
								char **command_arg, int index, int len)
{
	if (command_arg[index][0] == '>')
	{
		command->redirection_outfile = 1;
		if (command_arg[index][1] == '>')
			command->redirection_outfile++;
		if (command->outfile)
			free(command->outfile);
		command->outfile = ft_substr(command_arg[index + 1], 0, len);
	}
	else if (command_arg[index][0] == '<')
	{
		command->redirection_infile = 1;
		if (command_arg[index][1] == '<')
			command->redirection_infile++;
		if (command->infile)
			free(command->infile);
		command->infile = ft_substr(command_arg[index + 1], 0, len);
	}
	else
		command->arguments = ft_split(command_arg[index], ' ');
}

// Imprimir algunos datos de cada comando y free de las estructuras
static void	print_commands(t_command **commands_dir)
{
	int			i;
	int			num_command;
	t_command	*commands;

	i = 0;
	commands = *commands_dir;
	while ((commands->simple_commands)[i])
	{
		printf("\n\n");
		printf("out: %s (%d)\nin: %s (%d)\n", \
		((commands->simple_commands)[i])->outfile, \
		((commands->simple_commands)[i])->redirection_outfile, \
		((commands->simple_commands)[i])->infile, \
		((commands->simple_commands)[i])->redirection_infile);
		num_command = 0;
		if (((commands->simple_commands)[i])->arguments)
		{
			while ((((commands->simple_commands)[i])->arguments)[num_command])
			{
				printf("arg: %s\n", \
				(((commands->simple_commands)[i])->arguments)[num_command]);
				free((((commands->simple_commands)[i])->arguments) \
					[num_command]);
				num_command++;
			}
			free(((commands->simple_commands)[i])->arguments);
		}
		free(((commands->simple_commands)[i])->outfile);
		free(((commands->simple_commands)[i])->infile);
		free((commands->simple_commands)[i]);
		i++;
	}
	printf("\n\n");
	free(commands->simple_commands);
	free(commands);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:16:19 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/14 12:34:29 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	create_argument(t_simple_command *command, char *arg);
void		free_commands(t_command **commands_dir);

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
		return (free_commands(&commands), \
				free_double_array((void **)command_args), NULL);
	return (commands);
}

// Iterar y juntar argumentos para construir la estructura
static int	create_and_append_simple_command(t_command	*commands, \
											char ***command_args)
{
	int			i;
	int			num_command;

	i = -1;
	num_command = 0;
	while ((*command_args)[++i] && (*command_args)[i][0])
	{
		if (!(commands->simple_commands)[num_command])
		{
			(commands->simple_commands)[num_command] = (t_simple_command *) \
			ft_calloc(1, sizeof(t_simple_command));
			((commands->simple_commands)[num_command])->infile = 0;
			((commands->simple_commands)[num_command])->outfile = 1;
		}
		if ((*command_args)[i][0] == '|')
			num_command++;
		else if (create_simple_command(\
				&(commands->simple_commands)[num_command], *command_args, i))
			return (1);
		if ((*command_args)[i][0] == '>' || (*command_args)[i][0] == '<')
			i++;
	}
	commands->number_simple_commands = ++num_command;
	free_double_array((void **)(*command_args));
	return (0);
}

// Guardar datos y comprobar que se guardan correctamente
static int	create_simple_command(t_simple_command **command_info, \
								char **command_arg, int index)
{
	t_simple_command	*command;

	command = *command_info;
	if (!command)
		return (1);
	if (command_arg[index][0] == '>')
	{
		command->redirection_outfile = 1;
		if (command_arg[index][1] == '>')
			command->redirection_outfile++;
		check_access_outfile(command, command_arg[index + 1]);
		if (command->outfile == -1)
			return (1);
	}
	else if (command_arg[index][0] == '<')
	{
		command->redirection_infile = 1;
		if (command_arg[index][1] == '<')
			command->redirection_infile++;
		check_access_infile(command, command_arg[index + 1]);
		if (command->infile == -1)
			return (1);
	}
	else if (command->arguments)
		create_argument(command, command_arg[index]);
	else
		command->arguments = ft_split(command_arg[index], ' ');
	return (0);
}

static void	create_argument(t_simple_command *command, char *arg)
{
	char	*command_line;
	char	*aux;
	int		i;

	i = 0;
	command_line = ft_substr((command->arguments)[0], 0, \
								ft_strlen((command->arguments)[0]));
	while ((command->arguments)[++i])
	{
		aux = ft_strjoin(command_line, " ");
		free(command_line);
		command_line = ft_strjoin(aux, (command->arguments)[i]);
		free(aux);
	}
	aux = ft_strjoin(command_line, " ");
	free(command_line);
	command_line = ft_strjoin(aux, arg);
	free_double_array((void **)command->arguments);
	command->arguments = ft_split(command_line, ' ');
	free(command_line);
	free(aux);
}

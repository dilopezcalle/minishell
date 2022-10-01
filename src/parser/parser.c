/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:16:19 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 10:03:37 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	create_argument(t_simple_command *command, char *arg);
void		free_commands(t_command **commands_dir);

// Crea la estructura general de los comandos que se utilizarán
t_command	*parser(char *command_line, char	**envp)
{
	t_command	*commands;
	char		**command_args;
	int			num_command;
	int			i;

	command_args = lexer(command_line, envp);
	if (!command_args)
		return (0);
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
	if (!(*command_info))
		return (1);
	if (command_arg[index][0] == '>')
	{
		(*command_info)->redirection_outfile = 1;
		if (command_arg[index][1] == '>')
			(*command_info)->redirection_outfile++;
		if (check_access_outfile((*command_info), command_arg[index + 1]))
			return (1);
	}
	else if (command_arg[index][0] == '<')
	{
		(*command_info)->redirection_infile = 1;
		if (command_arg[index][1] == '<')
			(*command_info)->redirection_infile++;
		if (check_access_infile((*command_info), command_arg[index + 1]))
			return (1);
	}
	else if ((*command_info)->arguments)
		create_argument((*command_info), command_arg[index]);
	else
		(*command_info)->arguments = ft_split(command_arg[index], ' ');
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

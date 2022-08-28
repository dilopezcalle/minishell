/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:16:19 by dilopez-          #+#    #+#             */
/*   Updated: 2022/08/28 12:06:45 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "libft.h"

char		**lexer(char *command_line);
static int	create_and_append_simple_command(t_simple_command **command_info, char **command_arg, int i);

t_command	*parser(char *command_line)
{
	t_command	*commands;
	char		**command_args;
	int			num_command;
	int			i;

	command_args = lexer(command_line);
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
	commands->simple_commands = (t_simple_command **)ft_calloc((num_command + 1), sizeof(t_simple_command *));
	if (!commands->simple_commands)
		return (0);
	i = 0;
	num_command = 0;
	while (command_args[i])
	{
		if (!(commands->simple_commands)[num_command])
			(commands->simple_commands)[num_command] = (t_simple_command *)ft_calloc(1, sizeof(t_simple_command));
		if (command_args[i][0] == '|')
			num_command++;
		else if (create_and_append_simple_command(&(commands->simple_commands)[num_command], command_args, i))
			return (0);
		if (command_args[i][0] == '>' || command_args[i][0] == '<')
			i++;
		i++;
	}
	i = 0;
	while ((commands->simple_commands)[i])
	{
		printf("\n\n");
		printf("out: %s (%d)\nin: %s (%d)\n", ((commands->simple_commands)[i])->outfile, ((commands->simple_commands)[i])->redirection_outfile, ((commands->simple_commands)[i])->infile, ((commands->simple_commands)[i])->redirection_infile);
		num_command = 0;
		if (((commands->simple_commands)[i])->arguments)
			while ((((commands->simple_commands)[i])->arguments)[num_command])
			{
				printf("arg: %s\n", (((commands->simple_commands)[i])->arguments)[num_command]);
				num_command++;
			}
		i++;
	}
	return (0);
}

static int	create_and_append_simple_command(t_simple_command **command_info, char **command_arg, int index)
{
	t_simple_command	*command;
	int					symbol;
	int					i;

	command = *command_info;
	if (command_arg[index][0] == '>')
	{
		if (command_arg[index][1] == '>')
			command->redirection_outfile = 2;
		else
			command->redirection_outfile = 1;
		if (command->outfile)
			free(command->outfile);
		command->outfile = ft_substr(command_arg[index + 1], 0, ft_strlen(command_arg[index + 1]));
	}
	else if (command_arg[index][0] == '<')
	{
		if (command_arg[index][1] == '<')
			command->redirection_infile = 2;
		else
			command->redirection_infile = 1;
		if (command->infile)
			free(command->infile);
		command->infile = ft_substr(command_arg[index + 1], 0, ft_strlen(command_arg[index + 1]));
	}
	else
		command->arguments = ft_split(command_arg[index], ' ');
	return (0);
}

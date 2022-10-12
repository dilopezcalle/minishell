/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:16:19 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 15:36:39 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	create_argument(t_simple_command *command, char *arg);
char		**copy_tokens_to_array(t_token **ar_token);
void		free_commands(t_command **commands_dir);
char		**ft_copy_double_array(char **envp_main);
void		free_ar_token(t_token **ar_token);
int			check_syntax_errors(char **separate);

// Crea la estructura general de los comandos que se utilizarán
t_command	*parser(char *command_line, char **envp)
{
	t_command	*commands;
	t_token		*ar_token;
	char		**command_args;
	int			num_command;
	int			i;

	ar_token = lexer(command_line, envp);
	i = 0;
	if (!ar_token->str)
		return (0);
	command_args = copy_tokens_to_array(&ar_token);
	if (!command_args)
		return (free_ar_token(&ar_token), NULL);
	i = -1;
	num_command = 1;
	while (command_args[++i])
		if (!ar_token[i].quote[0] && command_args[i][0] == '|')
			num_command++;
	commands = (t_command *) ft_calloc(1, sizeof(t_command));
	if (!commands)
		return (free_ar_token(&ar_token), NULL);
	commands->simple_commands = (t_simple_command **) \
					ft_calloc((num_command + 1), sizeof(t_simple_command *));
	if (!commands->simple_commands)
		return (free_ar_token(&ar_token), NULL);
	if (create_and_append_simple_command(commands, ar_token, &command_args))
		return (free_commands(&commands), \
				free_double_array((void **)command_args), \
				free_ar_token(&ar_token), NULL);
	return (free_ar_token(&ar_token), commands);
}

char	**copy_tokens_to_array(t_token **ar_token)
{
	char	**command_args;
	int		i;

	i = 0;
	while ((*ar_token)[i].str)
		i++;
	command_args = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!command_args)
		return (0);
	i = 0;
	while ((*ar_token)[i].str)
	{
		command_args[i] = ft_strdup((*ar_token)[i].str);
		free((*ar_token)[i].str);
		i++;
	}
	command_args[i] = 0;
	if (check_syntax_errors(command_args))
		return (free_double_array((void **)command_args), NULL);
	return (command_args);
}


// Iterar y juntar argumentos para construir la estructura
static int	create_and_append_simple_command(t_command	*commands, \
											t_token *ar_token, char ***command_args)
{
	int			i;
	int			num_command;

	i = -1;
	num_command = 0;
	while ((*command_args)[++i]/* && (*command_args)[i][0]*/)
	{
		if (!(commands->simple_commands)[num_command])
		{
			(commands->simple_commands)[num_command] = (t_simple_command *) \
			ft_calloc(1, sizeof(t_simple_command));
			((commands->simple_commands)[num_command])->infile = 0;
			((commands->simple_commands)[num_command])->outfile = 1;
		}
		if (!ar_token[i].quote[0] && (*command_args)[i][0] == '|')
			num_command++;
		else if (create_simple_command(\
				&(commands->simple_commands)[num_command], ar_token, *command_args, i))
			return (1);
		if (!ar_token[i].quote[0] && ((*command_args)[i][0] == '>' || (*command_args)[i][0] == '<'))
			i++;
	}
	commands->number_simple_commands = ++num_command;
	free_double_array((void **)(*command_args));
	return (0);
}

// Guardar datos y comprobar que se guardan correctamente
static int	create_simple_command(t_simple_command **command_info, \
								t_token *ar_token, char **command_arg, int index)
{
	if (!(*command_info))
		return (1);
	if (!ar_token[index].quote[0] && command_arg[index][0] == '>')
	{
		(*command_info)->redirection_outfile = 1;
		if (command_arg[index][1] == '>')
			(*command_info)->redirection_outfile++;
		if (check_access_outfile((*command_info), command_arg[index + 1]))
			return (1);
	}
	else if (!ar_token[index].quote[0] && command_arg[index][0] == '<')
	{
		(*command_info)->redirection_infile = 1;
		if (command_arg[index][1] == '<')
			(*command_info)->redirection_infile++;
		if (check_access_infile((*command_info), command_arg[index + 1]))
			return (1);
	}
	else/* if ((*command_info)->arguments)*/
		create_argument((*command_info), command_arg[index]);
	// else
	// 	(*command_info)->arguments = ft_split(command_arg[index], ' ');
	return (0);
}

static void	create_argument(t_simple_command *command, char *arg)
{
	char	**aux;
	int		i;

	i = 0;
	if (!command->arguments)
	{
		command->arguments = (char **)ft_calloc(i + 2, sizeof(char *));
		command->arguments[0] = ft_strdup(arg);
		command->number_arguments = 1;
		return ;
	}
	aux = (char **)ft_calloc(command->number_arguments + 2, sizeof(char *));
	i = 0;
	while (i < command->number_arguments)
	{
		aux[i] = ft_strdup(command->arguments[i]);
		free(command->arguments[i]);
		i++;
	}
	aux[i++] = ft_strdup(arg);
	free(command->arguments);
	command->arguments = (char **)ft_calloc(i + 1, sizeof(char *));
	while (--i >= 0)
	{
		command->arguments[i] = ft_strdup(aux[i]);
		free(aux[i]);
	}
	free(aux);
	command->number_arguments++;
}

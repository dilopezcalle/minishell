/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:34:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/08/24 14:20:39 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Separar en "argumentos" los comandos con sus argumentos, el input y el output
char	**lexer(char *command_line)
{
	char	**separate_line;
	char	**command_args;
	int		start;
	int		i;

	i = 1;
	start = -1;
	command_line = check_quotation_marks_and_symbols(command_line);
	separate_line = ft_split(command_line, ' ');
	while (separate_line[++start])
		if (separate_line[start][0] == '|' || separate_line[start][0] == '>' \
			|| separate_line[start][0] == '<')
			i++;
	command_args = (char **)ft_calloc((i + 5), sizeof(char *));
	if (!command_line || !command_args)
		return (0);
	i = -1;
	start = 0;
	while (separate_line[++i])
	{
		start = check_end_command(&command_args, separate_line, i, start);
		if (start == -1)
			return (0);
	}
	i = 0;
	while (command_args[i])
	{
		printf("%s\n", command_args[i]);
		i++;
	}
	return (command_args);
}

// Verifica que los simbolos <, > y \ no estén entre comillas
static char	*check_quotation_marks_and_symbols(char *command_line)
{
	int		i;
	char	symbol;

	i = 0;
	while (command_line[i])
	{
		if (command_line[i] != '\0' && (command_line[i] == '\"' \
			|| command_line[i] == '\''))
		{
			symbol = command_line[i];
			while (command_line[i] && command_line[++i] != symbol)
				i++;
		}
		if (command_line[i] == '|' || command_line[i] == '>' \
			|| command_line[i] == '<')
		{
			symbol = command_line[i];
			command_line = put_spaces_around_char(command_line, i, symbol);
			if (!command_line)
				return (0);
			i += 2;
		}
		i++;
	}
	return (command_line);
}

// Pone dos espacios alrededor del caracter indicado por el índice del string
static char	*put_spaces_around_char(char *command_line, int index, char symbol)
{
	char	*new_command_line;
	char	*aux;
	char	*aux2;
	int		i;

	aux = ft_substr(command_line, 0, index);
	aux2 = (char *)malloc((ft_strlen(aux) + 4) * sizeof(char));
	if (!aux || !aux2)
		return (0);
	i = -1;
	while (aux[++i])
		aux2[i] = aux[i];
	if (command_line[index - 1] != symbol)
		aux2[i++] = ' ';
	aux2[i++] = symbol;
	if (command_line[index + 1] != symbol)
		aux2[i++] = ' ';
	aux2[i] = '\0';
	free(aux);
	aux = ft_substr(command_line, index + 1, ft_strlen(command_line));
	if (!aux)
		return (0);
	new_command_line = ft_strjoin(aux2, aux);
	free(aux);
	free(aux2);
	free(command_line);
	return (new_command_line);
}

// Comprueba si hay un >, < ó | que represente el final del comando
static int	check_end_command(char ***command_args, char **separate_line, \
								int i, int start)
{
	int	end;

	end = -1;
	if (i > 0 && separate_line[i - 1][0] == '|')
		if (append_command_array(command_args, separate_line, start - 1, start - 1))
			return (-1);
	if (separate_line[i][0] == '|' || separate_line[i][0] == '>' || separate_line[i][0] == '<')
		end = i - 1;
	else if (!separate_line[i + 1])
		end = i;
	if (i > 0 && (separate_line[i - 1][0] == '>' || separate_line[i - 1][0] == '<'))
		end = i;
	if (end != -1)
	{
		if (append_command_array(command_args, separate_line, start, end))
			return (-1);
		if (separate_line[i][0] == '>' || separate_line[i][0] == '<')
		{
			if (separate_line[i - 1][0] == '>' || separate_line[i - 1][0] == '<')
				start = i - 1;
			else
				start = i;
		}
		else
			start = i + 1;		
	}
	return (start);
}

// Agrega al final de el array command_args los strings 
// de los indices start y end de separate_line
static int	append_command_array(char ***command_args, char **separate_line, \
									int start, int end)
{
	char	**commands;
	char	*aux;
	int		i;

	commands = *command_args;
	i = 0;
	while (commands[i])
		i++;
	if ((start > end && (separate_line[start][0] == '>' || separate_line[start][0] == '<')) \
		|| end - 1 == start && (separate_line[end][0] == '>' || separate_line[end][0] == '<'))
		return (0);
	commands[i] = ft_substr(separate_line[start], 0, ft_strlen(separate_line[start]));
	start++;
	while (start <= end)
	{
		if (separate_line[start - 1][0] != '>' && separate_line[start - 1][0] != '<')
			aux = ft_strjoin(commands[i], " ");
		else
			aux = ft_strjoin(commands[i], "");
		if (!aux)
			return (1);
		free(commands[i]);
		commands[i] = ft_strjoin(aux, separate_line[start]);
		if (!commands[i])
			return (1);
		free(aux);
		start++;
	}
	if (!commands[i])
		return (1);
	return (0);
}

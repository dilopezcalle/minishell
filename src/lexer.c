/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:34:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/08/19 19:16:26 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Separar en "argumentos" los comandos con sus argumentos, el input y el output
char	**lexer(char *command_line)
{
	char	**separate_commands;
	int		i;

	command_line = check_quotation_marks_and_symbols(command_line);
	if (!command_line)
		return (0); // Provisional
	separate_commands = ft_split(command_line, ' ');
	i = 0;
	while (separate_commands[i])
	{
		printf("%s\n", separate_commands[i]);
		i++;
	}
	free(command_line);
	return (0);
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
			i++;
			while (command_line[i] != symbol)
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
	aux2[i++] = ' ';
	aux2[i++] = symbol;
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

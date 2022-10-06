/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 09:34:54 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/06 09:18:34 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// Separar en "argumentos" los comandos con sus argumentos, el input y el output
t_token	*lexer(char *command_line, char	**envp)
{
	t_token	*ar_token;
	char	**command_args;
	char	**separate_line;
	int		size;
	int		i;

	size = 1;
	i = -1;
	ar_token = tokens(command_line, envp);
	free(command_line);
	return (ar_token);
}























//Comprueba si hay un >, < ó | que represente el final de cada comando / archivo
static int	mix_args_command(char ***command_args, char **separate, int i)
{
	int	end;
	int	start;

	start = 0;
	while (separate[++i])
	{
		end = check_end_command(separate, i, &start);
		if (end != -1 && start <= end)
		{
			if (append_command_array(command_args, separate, start, end))
				return (free_double_array((void **)*command_args), -1);
			start = i + 1;
		}
		if ((separate[i][0] == '|' || separate[i][0] == '>' \
			|| separate[i][0] == '<') \
			&& append_command_array(command_args, separate, i, i))
			return (free_double_array((void **)*command_args), -1);
	}
	return (0);
}

static int	check_end_command(char **separate, int i, int *start)
{
	int	end;

	end = -1;
	if (separate[i][0] == '|' || separate[i][0] == '>' \
		|| separate[i][0] == '<')
		end = i - 1;
	if (i > 0 && (separate[i - 1][0] == '|' || separate[i - 1][0] == '>' \
		|| separate[i - 1][0] == '<'))
	{
		*start = i;
		if (separate[i - 1][0] == '>' || separate[i - 1][0] == '<')
			end = i;
	}
	if (!separate[i + 1])
		end = i;
	if (end != -1 && separate[end][0] == '|')
		end--;
	return (end);
}

// Agrega al final de el array command_args los strings 
// de los indices start y end de separate_line
static int	append_command_array(char ***command_args, char **separate, \
									int start, int end)
{
	char	**commands;
	char	*aux;
	int		i;

	commands = *command_args;
	i = 0;
	while (commands[i])
		i++;
	commands[i] = ft_substr(separate[start], 0, ft_strlen(separate[start]));
	while (++start <= end)
	{
		if (separate[start - 1][0] != '>' && separate[start - 1][0] != '<')
			aux = ft_strjoin(commands[i], " ");
		else
			aux = ft_strjoin(commands[i], "");
		if (!aux)
			return (1);
		free(commands[i]);
		commands[i] = ft_strjoin(aux, separate[start]);
		free(aux);
		if (!commands[i])
			return (1);
	}
	return (0);
}

/*
	if (!separate_line || check_syntax_errors(separate_line))
		return (free_double_array((void **)separate_line), NULL);
	while (separate_line[++i])
	{
		if (separate_line[i][0] == '|' || separate_line[i][0] == '>' \
			|| separate_line[i][0] == '<')
			size += 2;
		if (i > 2 && (separate_line[i - 2][0] == '>' \
			|| separate_line[i - 2][0] == '<'))
			size++;
	}
	command_args = (char **)ft_calloc((size + 1), sizeof(char *));
	if (!command_args \
		|| mix_args_command(&command_args, separate_line, -1) == -1)
		return (free_double_array((void **)separate_line), NULL);
	return (free_double_array((void **)separate_line), command_args);
	*/
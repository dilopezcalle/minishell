/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:11:18 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 16:37:54 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access_parser.h"
#include <sys/errno.h>

// Comprobar que exista el fichero de un comando en las rutas del environment
int	access_parser(t_command *commands, char *envp[])
{
	t_simple_command	*command;
	int					i;
	char				**paths;
	char				*command_path;

	i = 0;
	paths = ft_get_paths(envp);
	while ((commands->simple_commands)[i])
	{
		command = (commands->simple_commands)[i];
		if (!command->arguments)
			return (free_double_array((void **)paths), 1);
		command_path = ft_get_commands_path((command->arguments)[0], paths);
		if (!command_path && !is_command_builtin((command->arguments)[0]))
		{
			free_double_array((void **)paths);
			printf("minishell: %s: command not found\n", \
					(command->arguments)[0]);
			return (1);
		}
		g_exit_status = 0;
		command->path = command_path;
		i++;
	}
	free_double_array((void **)paths);
	return (0);
}

// Obtener todas las rutas de los comandos del environment
static char	**ft_get_paths(char *envp[])
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (envp[i])
	{
		paths = ft_split(envp[i] + 5, ':');
		return (paths);
	}
	else
		return (NULL);
}

// Contruir el string que representa el path de un comando
static char	*ft_get_commands_path(char *command, char **paths)
{
	char	*command_path;
	char	*path;
	char	*temp;
	int		i;

	if (is_command_builtin(command) || command[0] == '\0' || paths == NULL)
		return (0);
	i = 0;
	path = 0;
	while (paths[i])
	{
		command_path = ft_strjoin("/", command);
		temp = ft_strjoin(paths[i], command_path);
		if (access(command, F_OK) == 0)
		{
			path = ft_strdup(command);
			free(temp);
		}
		else if (access(temp, F_OK) == 0)
			path = temp;
		else
		{
			g_exit_status = 127;
			free(temp);
		}
		free(command_path);
		i++;
	}
	return (path);
}

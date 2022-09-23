/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:11:18 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/23 09:42:33 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access_parser.h"

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
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

// Contruir el string que representa el path de un comando
static char	*ft_get_commands_path(char *command, char **paths)
{
	char	*command_path;
	char	*path;
	char	*temp;
	int		i;

	if (is_command_builtin(command))
		return (0);
	i = 0;
	path = 0;
	while (paths[i])
	{
		command_path = ft_strjoin("/", command);
		temp = ft_strjoin(paths[i], command_path);
		if (access(temp, F_OK) == 0)
			path = temp;
		else
			free(temp);
		free(command_path);
		i++;
	}
	return (path);
}

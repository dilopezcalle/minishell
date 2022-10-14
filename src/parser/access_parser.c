/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:11:18 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/14 17:56:59 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

#include "access_parser.h"
#include "structs.h"
#include "libft.h"
#include "utils.h"

static char	**ft_get_paths(char *envp[]);
static char	*ft_get_commands_path(char *command, char **paths);

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
			printf("minishell: %s: command not found\n", \
				(command->arguments)[0]);
			g_exit_status = 127;
		}
		command->path = command_path;
		i++;
	}
	free_double_array((void **)paths);
	return (0);
}

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

static char	*ft_get_commands_path(char *command, char **paths)
{
	char	*command_path;
	char	*path;
	char	*temp;
	int		i;

	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	if (is_command_builtin(command) || command[0] == '\0' || paths == NULL)
		return (0);
	i = -1;
	path = 0;
	while (paths[++i])
	{
		command_path = ft_strjoin("/", command);
		temp = ft_strjoin(paths[i], command_path);
		if (access(temp, F_OK) == 0)
			path = temp;
		else
			free(temp);
		free(command_path);
	}
	return (path);
}

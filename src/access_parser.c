/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:11:18 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/12 16:58:25 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "access_parser.h"

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
		command_path = ft_get_commands_path((command->arguments)[0], paths);
		if (!command_path)
		{
			printf("ACCESS \'%s\'\n", (command->arguments)[0]);
			return (1);
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
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

static char	*ft_get_commands_path(char *command, char **paths)
{
	char	*command_path;
	char	*path;
	char	*temp;
	int		i;

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

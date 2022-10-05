/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 09:21:48 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/05 08:13:55 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	cd_builtin(t_simple_command *command, char **envp[])
{
	char	*path;

	//path = getcwd(NULL, 0);
	if (!command->arguments[1])
		return (cd_without_argument(command, envp));
	if (command->arguments[1][0] == '-' && command->arguments[1][1] == '\0')
		path = ft_getenv("OLDPWD", *envp);
	else
		path = command->arguments[1];
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}

static int	cd_without_argument(t_simple_command *command, char **envp[])
{
	char	*home;

	home = ft_getenv("HOME", *envp);
	if (!home)
		return (1);
	if (chdir(home) != 0)
	{
		printf("minishell: cd: %s: %s\n", home, strerror(errno));
		free(home);
		perror("minishell: cd: ~");
		return (1);
	}
	free(home);
	return (0);
}

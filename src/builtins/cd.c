/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 09:21:48 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/05 16:46:00 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	cd_builtin(t_simple_command *command, char **envp[])
{
	char	*path;
	char	*pwd;

	if (!command->arguments[1])
		return (cd_without_argument(command, envp));
	if (command->arguments[1][0] == '-' && command->arguments[1][1] == '\0')
		path = ft_getenv("OLDPWD", *envp);
	else
		path = command->arguments[1];
	if (export_pwd("OLDPWD=", envp))
		return (1);
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (export_pwd("PWD=", envp))
		return (1);
	return (0);
}

static int	cd_without_argument(t_simple_command *command, char **envp[])
{
	char	*home;

	home = ft_getenv("HOME", *envp);
	if (!home)
		return (1);
	if (export_pwd("OLDPWD=", envp))
		return (1);
	if (chdir(home) != 0)
	{
		printf("minishell: cd: %s: %s\n", home, strerror(errno));
		free(home);
		perror("minishell: cd: ~");
		return (1);
	}
	if (export_pwd("PWD=", envp))
		return (1);
	free(home);
	return (0);
}

static int	export_pwd(char *var, char **envp[])
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	path = ft_strjoin(var, pwd);
	if (!path)
		return (1);
	if (export_builtin(path, envp))
		return (free(pwd), free(path), 1);
	printf("%s\n", path);
	return (free(pwd), free(path), 0);
}
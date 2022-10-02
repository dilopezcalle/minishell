/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 09:21:48 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 18:01:58 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	cd_builtin(t_simple_command *command)
{
	char	*path;

	if (!command->arguments[1])
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("minishell: cd: ~");
			return (1);
		}
		return (0);
	}
	path = command->arguments[1];
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}

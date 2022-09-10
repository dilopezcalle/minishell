/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:38:24 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/08 09:16:51 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void	iter_execute_commands(t_command *commands, char *envp[]);

void	executor(t_command *commands, char *envp[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("ERROR fork\n");
		exit(1);
	}
	else if (!pid)
		execute_commands(commands, envp);
	else
		wait(NULL);
}

void	iter_execute_commands(t_command *commands, char *envp[])
{
	int	fd[2];
	int	pid;
	int	i;

	if (pipe(fd) == -1)
	{
		printf("ERROR pipe\n");
		exit(1);
	}
	i = 0;
	while (i < commands->number_simple_commands)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("ERROR fork\n");
			exit(1);
		}
		else if (!pid)
			execute_command((commands->simple_commands)[i], fd, envp);
		close(fd[1]);
		wait(NULL);
		fd[1] = dup(fd[0]);
		close(fd[0]);
		i++;
	}
}
/*
void	execute_command(t_simple_command )
{

}
*/

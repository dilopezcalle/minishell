/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:38:24 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/14 12:36:52 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
		iter_execute_commands(commands, envp);
	else
		wait(NULL);
}

static void	iter_execute_commands(t_command *commands, char *envp[])
{
	int	fd[2];
	int	i;

	i = 0;
	while (i < commands->number_simple_commands)
	{
		if (pipe(fd) == -1)
		{
			printf("ERROR pipe\n");
			exit(1);
		}
		create_and_execute_child(commands, fd, envp, i);
		i++;
	}
}

static void	create_and_execute_child(t_command *commands, int fd[2], \
										char *envp[], int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("ERROR fork\n");
		exit(1);
	}
	else if (!pid && i + 1 < commands->number_simple_commands)
		execute_command((commands->simple_commands)[i], fd, envp, 0);
	else if (!pid && i + 1 >= commands->number_simple_commands)
		execute_command((commands->simple_commands)[i], fd, envp, 1);
	else
	{
		wait(NULL);
		close(fd[1]);
		if (((commands->simple_commands)[i + 1])->infile == 0)
			((commands->simple_commands)[i + 1])->infile = dup(fd[0]);
		close(fd[0]);
	}
}

static void	execute_command(t_simple_command *command, int fd[2], \
							char *envp[], int last)
{
	close(fd[0]);
	dup2(command->infile, 0);
	if (command->outfile != 1)
	{
		dup2(command->outfile, 1);
		close(command->outfile);
	}
	else if (last == 0)
		dup2(fd[1], 1);
	close(fd[1]);
	close(command->infile);
	execve(command->path, command->arguments, envp);
}

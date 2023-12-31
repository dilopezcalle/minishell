/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:38:24 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/14 19:10:50 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <sys/wait.h>
#include <stddef.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "builtin_parent.h"
#include "builtin_child.h"
#include "executor.h"
#include "signals.h"
#include "utils.h"

static int	create_and_execute_child(t_command *commands, int fd[2], \
										char *envp[], int i);
static void	execute_command(t_simple_command *command, int fd[2], \
							char *envp[], int last);
static int	parent_control(t_command *commands, int fd[2], int i, int pid);

void	executor(t_command *commands, char **envp[])
{
	int	fd[2];
	int	i;

	i = 0;
	if (is_command_builtin(commands->simple_commands[0]-> arguments[0]) \
		&& commands->number_simple_commands == 1 \
		&& execute_parent_builtin(commands->simple_commands[0], envp))
		return ;
	while (i < commands->number_simple_commands)
	{
		if (pipe(fd) == -1)
		{
			perror("minishell: pipe");
			g_exit_status = errno;
			return ;
		}
		signal(SIGINT, 0);
		signal(SIGQUIT, 0);
		create_and_execute_child(commands, fd, *envp, i);
		i++;
	}
	if (g_exit_status == 2)
		g_exit_status = 130;
	if (g_exit_status == 3)
		g_exit_status = 131;
}

static int	create_and_execute_child(t_command *commands, int fd[2], \
										char *envp[], int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		g_exit_status = errno;
		return (1);
	}
	if (!pid && !commands->simple_commands)
		exit(0);
	if (!pid && i + 1 < commands->number_simple_commands)
		execute_command((commands->simple_commands)[i], fd, envp, 0);
	else if (!pid && i + 1 >= commands->number_simple_commands)
		execute_command((commands->simple_commands)[i], fd, envp, 1);
	parent_control(commands, fd, i, pid);
	return (1);
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
	if (is_command_builtin(command->arguments[0]))
		execute_child_builtin(command, envp);
	if (!command->path)
		exit (1);
	execve(command->path, command->arguments, envp);
}

static int	parent_control(t_command *commands, int fd[2], int i, int pid)
{
	int	result;

	signal(SIGINT, sig_handler_without_input);
	signal(SIGQUIT, sig_handler_without_input);
	close(fd[1]);
	waitpid(pid, &result, 0);
	if (result <= 255)
		g_exit_status = result;
	if (i + 1 >= commands->number_simple_commands)
		return (close(fd[0]), 0);
	if (((commands->simple_commands)[i + 1])->infile == 0)
		((commands->simple_commands)[i + 1])->infile = dup(fd[0]);
	close(fd[0]);
	return (0);
}

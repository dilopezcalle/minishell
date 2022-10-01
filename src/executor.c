/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:38:24 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 08:54:24 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// Recorre todos los comandos y crea las pipes que los comunicarán
void	executor(t_command *commands, char *envp[])
{
	int	fd[2];
	int	i;

	i = 0;
	if (is_command_builtin(commands->simple_commands[0]-> arguments[0]) \
		&& commands->number_simple_commands == 1 \
		&& execute_parent_builtin(commands->simple_commands[0]))
	{
		g_exit_status = 1;
		return ;
	}
	while (i < commands->number_simple_commands)
	{
		if (pipe(fd) == -1)
		{
			perror("minishell: pipe");
			g_exit_status = 1;
			break ;
		}
		signal(SIGINT, 0);
		create_and_execute_child(commands, fd, envp, i);
		i++;
	}
	g_exit_status = 0;
}

// Crea un proceso hijo para luego ejecutar un comando en él
static int	create_and_execute_child(t_command *commands, int fd[2], \
										char *envp[], int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (!pid && !commands->simple_commands)
		exit(0);
	if (!pid && i + 1 < commands->number_simple_commands)
		execute_command((commands->simple_commands)[i], fd, envp, 0);
	else if (!pid && i + 1 >= commands->number_simple_commands)
		execute_command((commands->simple_commands)[i], fd, envp, 1);
	else
	{
		signal(SIGINT, sig_handler_without_input);
		close(fd[1]);
		wait(NULL);
		if (i + 1 >= commands->number_simple_commands)
		{
			close(fd[0]);
			return (0);
		}
		if (((commands->simple_commands)[i + 1])->infile == 0)
			((commands->simple_commands)[i + 1])->infile = dup(fd[0]);
		close(fd[0]);
	}
	return (1);
}

// Ejecuta comando hijos y controla la salida y entrada estandard
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
	{
		dup2(fd[1], 1);
	}
	close(fd[1]);
	if (is_command_builtin(command->arguments[0]))
		execute_child_builtin(command);
	execve(command->path, command->arguments, envp);
}

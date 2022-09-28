/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:38:24 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/27 07:49:23 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// "Liberar" las señales controladas para ejecutar los comandos en hijos
void	executor(t_command *commands, char *envp[])
{
	int	pid;

	signal(SIGINT, 0);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		exit(1);
	}
	else if (!pid)
	{
		signal(SIGINT, 0);
		iter_execute_commands(commands, envp);
	}
	else
	{
		signal(SIGINT, sig_handler_without_input);
		wait(NULL);
	}
}

// Recorre todos los comandos y crea las pipes que los comunicarán
static void	iter_execute_commands(t_command *commands, char *envp[])
{
	int	fd[2];
	int	i;

	i = 0;
	while (i < commands->number_simple_commands)
	{
		if (pipe(fd) == -1)
		{
			perror("minishell: pipe");
			exit(1);
		}
		create_and_execute_child(commands, fd, envp, i);
		i++;
	}
}

// Crea un proceso hijo para luego ejecutar un comando en él
static void	create_and_execute_child(t_command *commands, int fd[2], \
										char *envp[], int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		exit(1);
	}
	if (!pid)
		signal(SIGINT, 0);
	if (!pid && !commands->simple_commands)
		exit(0);
	if (!pid && i + 1 < commands->number_simple_commands)
		execute_command((commands->simple_commands)[i], fd, envp, 0);
	else if (!pid && i + 1 >= commands->number_simple_commands)
		execute_command((commands->simple_commands)[i], fd, envp, 1);
	else
	{
		wait(NULL);
		close(fd[1]);
		if (i + 1 >= commands->number_simple_commands)
			exit(0);
		if (((commands->simple_commands)[i + 1])->infile == 0)
			((commands->simple_commands)[i + 1])->infile = dup(fd[0]);
		close(fd[0]);
	}
}

// Ejecuta un comando y controla la salida y entrada estandard
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

// Señal en caso de ctrl + C (cat o grep a secas)
static void	sig_handler_without_input(int signum)
{
	signum = 0;
	printf("\n");
}

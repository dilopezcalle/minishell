/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:52:00 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/13 17:01:17 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <sys/errno.h>
#include <stddef.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "files_access.h"
#include "signals.h"
#include "libft.h"
#include "lexer.h"

static void	dub_stdin_infile(t_simple_command *command, char *file_name);
static char	*readline_infile(char *end_word);
static int	fork_error_infile(void);

int	check_access_outfile(t_simple_command *command, char *file_name)
{
	int	fd;

	fd = -1;
	if (command->redirection_outfile == 1)
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file_name, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		g_exit_status = 1;
		printf("minishell: %s: %s\n", file_name, strerror(2));
		command->outfile = -1;
		return (1);
	}
	if (command->outfile != 1)
		close(command->outfile);
	command->outfile = fd;
	return (0);
}

int	check_access_infile(t_simple_command *command, char *file_name)
{
	int		fd;

	if (command->redirection_infile == 2)
	{
		command->infile = 0;
		dub_stdin_infile(command, file_name);
		return (0);
	}
	fd = -1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		g_exit_status = 1;
		printf("minishell: %s: %s\n", file_name, strerror(errno));
		command->infile = -1;
		return (1);
	}
	if (command->infile != 0)
		close(command->infile);
	command->infile = fd;
	return (0);
}

static char	*readline_infile(char *end_word)
{
	char	*actual;
	char	*join;
	char	*aux;

	aux = readline("> ");
	join = 0;
	while (aux && ft_strncmp(aux, end_word, ft_strlen(end_word) + 1) != 0)
	{
		actual = ft_strjoin(aux, "\n");
		free(aux);
		if (!join)
			aux = ft_substr(actual, 0, ft_strlen(actual));
		else
		{
			aux = ft_strjoin(join, actual);
			free(join);
		}
		join = ft_substr(aux, 0, ft_strlen(aux));
		free(actual);
		free(aux);
		aux = readline("> ");
	}
	free(aux);
	return (join);
}

static void	dub_stdin_infile(t_simple_command *command, char *file_name)
{
	int		fd_pipe[2];
	int		pid;
	char	*join;

	signal(SIGINT, sig_handler_heredoc);
	signal(SIGQUIT, sig_handler);
	if (pipe(fd_pipe) == -1)
	{
		perror("minishell: pipe");
		exit(1);
	}
	pid = fork_error_infile();
	if (!pid)
	{
		join = readline_infile(file_name);
		if (!join)
			exit(0);
		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
		write(1, join, ft_strlen(join));
		free(join);
		exit(0);
	}
	dub_stdin_infile_2(fd_pipe, command);
}

static int	fork_error_infile(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		exit(1);
	}
	return (pid);
}

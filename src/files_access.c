/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:52:00 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/22 10:09:44 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "files_access.h"

// Guardar el fd de un fichero output dependiendo de su tipo de redirección
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
		printf("minishell: %s: %s\n", file_name, strerror(2));
		command->outfile = -1;
		return (1);
	}
	if (command->outfile != 1)
		close(command->outfile);
	command->outfile = fd;
	return (0);
}

// Guardar el fd de un fichero input dependiendo de su tipo de redirección
int	check_access_infile(t_simple_command *command, char *file_name)
{
	int		fd;
	char	*join;

	fd = -1;
	if (command->redirection_infile == 2)
	{
		command->infile = 0;
		join = readline_infile(file_name);
		if (!join)
			return (1);
		dub_stdin_infile(command, join);
		return (0);
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: %s\n", file_name, strerror(errno));
		command->infile = -1;
		return (1);
	}
	if (command->infile != 0)
		close(command->infile);
	command->infile = fd;
	return (0);
}

// En el caso de ("<<"), leer desde la entrada estándar y guardar string
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

// En el caso de ("<<"), guardar el string estándar en un fd
static void	dub_stdin_infile(t_simple_command *command, char *join)
{
	int		fd_pipe[2];
	int		pid;

	if (pipe(fd_pipe) == -1)
	{
		perror("minishell: pipe");
		exit(1);
	}
	pid = fork_error_infile();
	if (!pid)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		close(fd_pipe[1]);
		write(1, join, ft_strlen(join));
		free(join);
		exit(0);
	}
	signal(SIGINT, sig_handler);
	close(fd_pipe[1]);
	wait(NULL);
	command->infile = fd_pipe[0];
}

// Comprobar que el fork no de error (norminette)
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

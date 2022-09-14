/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:52:00 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/14 12:33:37 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "files_access.h"
#include "libft.h"

void	check_access_outfile(t_simple_command *command, char *file_name)
{
	int	fd;

	fd = -1;
	if (command->redirection_outfile == 1)
		fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file_name, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		printf("ERROR outfile: \'%s\'\n", file_name);
		command->outfile = -1;
		return ;
	}
	if (command->outfile != 1)
		close(command->outfile);
	command->outfile = fd;
}

void	check_access_infile(t_simple_command *command, char *file_name)
{
	int		fd;
	int		fd_pipe[2];
	int		pid;
	char	*join;

	fd = -1;
	if (command->redirection_infile == 2)
	{
		command->infile = 0;
		join = readline_infile(file_name);
		if (pipe(fd_pipe) == -1)
		{
			printf("ERROR pipe\n");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			printf("ERROR fork\n");
			exit(1);
		}
		else if (!pid)
		{
			close(fd_pipe[0]);
			dup2(fd_pipe[1], 1);
			close(fd_pipe[1]);
			write(1, join, ft_strlen(join));
			exit(0);
		}
		else
		{
			close(fd_pipe[1]);
			wait(NULL);
			command->infile = fd_pipe[0];
		}
		return ;
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR infile: \'%s\'\n", file_name);
		command->infile = -1;
		return ;
	}
	if (command->infile != 0)
		close(command->infile);
	command->infile = fd;
}

static char	*readline_infile(char *end_word)
{
	char	*actual;
	char	*join;
	char	*aux;
	int		len;

	len = ft_strlen(end_word);
	aux = readline("> ");
	join = 0;
	while (ft_strncmp(aux, end_word, len + 1) != 0)
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

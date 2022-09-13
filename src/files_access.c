/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:52:00 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/12 16:55:11 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "files_access.h"

void	check_access_outfile(t_simple_command *command, char *file_name, \
							int len)
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
		return ;
	}
	command->outfile = ft_substr(file_name, 0, len);
	close(fd);
}

void	check_access_infile(t_simple_command *command, char *file_name, int len)
{
	int	fd;

	fd = -1;
	command->infile = ft_substr(file_name, 0, len);
	if (command->redirection_infile == 2)
	{
		readline_infile(command->infile);
		return ;
	}
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("ERROR infile: \'%s\'\n", file_name);
		return ;
	}
	close(fd);
}

static void	readline_infile(char *end_word)
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
}

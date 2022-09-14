/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:14:32 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/14 11:42:14 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "structs.h"
#include "libft.h"

t_command	*parser(char *command_line);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			access_parser(t_command *commands, char *envp[]);
void		free_commands(t_command **commands_dir);
void		executor(t_command *commands, char *envp[]);

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*commands;
	char		*line;

	argc = 0;
	argv = 0;
	while (1)
	{
		line = readline("\x1B[32mMyshell>\x1B[0m ");
		//str = ft_substr("ls -la > outfile | ls -la | grep git", 0, 200);
		if (line[0] != '\0')
		{
			commands = parser(line);
			if (commands)
			{
				if (!access_parser(commands, envp))
					executor(commands, envp);
				free_commands(&commands);
			}
		}
		else
			free(line);
	}
	return (0);
}

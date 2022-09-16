/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:33:15 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/16 11:19:03 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *envp[])
{
	t_command	*commands;
	char		*line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		line = get_line();
		if (line[0] != '\0')
		{
			add_history(line);
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
}

char	*get_line(void)
{
	char	*line;

	line = readline("\x1B[32mMyshell>\x1B[0m ");
	if (!line || ft_strncmp(line, "exit", 5) == 0)
	{
		if (line)
			free(line);
		exit_program(0);
	}
	return(line);
}

void	sig_handler(int signum)
{
	if (rl_on_new_line() == -1)
		exit(-1);
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	exit_program(int code)
{
	printf("exit\n");
	exit(code);
}
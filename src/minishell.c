/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:33:15 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/25 13:58:35 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Lee la línea en búcle y llama al parser y executor
void	minishell(char *envp_main[])
{
	t_command	*commands;
	char		*line;
	char		**envp;

	envp = ft_copy_double_array(envp_main);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, exit_program);
		line = get_line();
		if (line[0] != '\0')
		{
			add_history(line);
			commands = parser(line);
			if (commands)
			{
				if (ft_strncmp(commands->simple_commands[0]->arguments[0], \
					"exit", 5) == 0)
					break ;
				if (!access_parser(commands, envp))
				{
					if (ft_strncmp(commands->simple_commands[0]->arguments[0], \
					"cd", 3) == 0 && commands->number_simple_commands == 1)
						cd_builtin(commands->simple_commands[0]);
					else
						executor(commands, envp);
				}
				free_commands(&commands);
			}
		}
		else
			free(line);
	}
	free_commands(&commands);
	exit_program(0);
	envp = 0;
}

// Ejecuta y devuelve readline. Comprueba que se escriba algo
char	*get_line(void)
{
	char	*line;

	line = readline("\001\033[0;33m\002MyShell \001\u27A4 \001\033[0m\002");
	if (!line)
		exit_program(0);
	return (line);
}

// Gestiona el ctrl + C
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

// Limpiar el historial y cerrar el programa
void	exit_program(int code)
{
	rl_clear_history();
	printf("exit\n");
	exit(code);
}

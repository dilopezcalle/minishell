/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:33:15 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 16:29:52 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

int		exit_builtin(t_simple_command *command);

// Lee la línea en búcle y llama al parser y executor
void	minishell(char *envp_main[])
{
	t_command	*commands;
	char		**envp;

	envp = ft_copy_double_array(envp_main);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		if (check_and_execute_line(get_line(), &envp))
			break ;
	}
	exit_program(g_exit_status);
}

static int	check_and_execute_line(char *line, char **envp[])
{
	t_command	*commands;

	if (!line)
		return (0);
	commands = parser(line, *envp);
	g_exit_status = 1;
	if (!commands)
		return (0);
	if (!access_parser(commands, *envp))
	{
		g_exit_status = 0;
		executor(commands, envp);
		if (commands->number_simple_commands == 1 && \
	ft_strncmp(commands->simple_commands[0]->arguments[0], "exit", 5) == 0 \
	&& !exit_builtin(commands->simple_commands[0]))
			return (free_commands(&commands), 1);
	}
	free_commands(&commands);
	return (0);
}

// Ejecuta y devuelve readline. Comprueba que se escriba algo
char	*get_line(void)
{
	char	*line;

	if (g_exit_status)
		line = readline("\001\033[0;31m\002concha_diminuta \001\u27A4 \001\033[0m\002");
	else
		line = readline("\001\033[0;33m\002concha_diminuta \001\u27A4 \001\033[0m\002");
	if (!line)
		exit_program(0);
	if (line[0] != '\0')
		add_history(line);
	else
	{
		free(line);
		line = 0;
	}
	return (line);
}

// Limpiar el historial y cerrar el programa
void	exit_program(int code)
{
	rl_clear_history();
	printf("exit\n");
	g_exit_status = code;
	exit(code);
}

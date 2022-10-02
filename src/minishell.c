/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 08:33:15 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/02 16:22:19 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_getenv.h"

// Lee la línea en búcle y llama al parser y executor
void	minishell(char *envp_main[])
{
	t_command	*commands;
	char		**envp;

	envp = ft_copy_double_array(envp_main);
	while (1)
	{
		//rl_catch_signals = 0;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		if (check_and_execute_line(get_line(), envp))
			break ;
	}
	exit_program(g_exit_status);
}

static int	check_and_execute_line(char *line, char **envp)
{
	t_command	*commands;

	if (!line)
		return (0);
	commands = parser(line, envp);
	if (!commands)
		return (0);
	if (!access_parser(commands, envp))
	{
		executor(commands, envp);
		if (ft_strncmp(commands->simple_commands[0]->arguments[0], \
			"exit", 5) == 0)
			return (free_commands(&commands), 1);
	}
	else
		g_exit_status = 1;
	free_commands(&commands);
	return (0);
}

// Ejecuta y devuelve readline. Comprueba que se escriba algo
char	*get_line(void)
{
	char	*line;

	if (g_exit_status)
		line = readline("\001\033[0;31m\002MyShell \001\u27A4 \001\033[0m\002");
	else
		line = readline("\001\033[0;33m\002MyShell \001\u27A4 \001\033[0m\002");
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

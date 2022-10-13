/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 08:49:37 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/13 17:02:23 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>

#include "signals.h"
#include "structs.h"

void	rl_replace_line(const char *text, int clear_undo);

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (rl_on_new_line() == -1)
			exit(-1);
		g_exit_status = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		if (rl_on_new_line() == -1)
			exit(-1);
		rl_redisplay();
	}
}

void	sig_handler_without_input(int signum)
{
	if (signum == SIGQUIT)
		printf ("Quit: 3\n");
	else if (signum == SIGINT)
		printf("\n");
}

void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
		exit(0);
	if (signum == SIGQUIT)
		if (rl_on_new_line() == -1)
			exit(-1);
}

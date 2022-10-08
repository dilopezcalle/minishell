/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 08:49:37 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/08 10:37:42 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

// Gestiona el ctrl + C
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

	}
}

// Señal en caso de ctrl + C (cat o grep a secas)
void	sig_handler_without_input(int signum)
{
	if (signum == SIGQUIT)
		printf ("Quit: 3\n");
	else if (signum == SIGINT)
		printf("\n");
}

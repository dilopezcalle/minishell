/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:31:26 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/18 15:50:32 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

void		sig_handler(int signum);
static void	sig_handler_without_input(int signum);

static void	execute_command(t_simple_command *command, int fd[2], \
							char *envp[], int last);
static void	create_and_execute_child(t_command *commands, int fd[2], \
										char *envp[], int i);
static void	iter_execute_commands(t_command *commands, char *envp[]);

#endif

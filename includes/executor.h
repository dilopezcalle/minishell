/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:31:26 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 18:12:55 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

static int	create_and_execute_child(t_command *commands, int fd[2], \
										char *envp[], int i);
static void	execute_command(t_simple_command *command, int fd[2], \
							char *envp[], int last);

int			execute_parent_builtin(t_simple_command *command, char	**envp);
int			execute_child_builtin(t_simple_command *command, char	**envp);
void		sig_handler_without_input(int signum);
int			is_command_builtin(char *command);
void		sig_handler(int signum);

#endif

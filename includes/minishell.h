/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:57 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/16 10:41:59 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include "libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>

char		*get_line(void);
t_command	*parser(char *command_line);
int			access_parser(t_command *commands, char *envp[]);
void		rl_replace_line(const char *text, int clear_undo);
void		executor(t_command *commands, char *envp[]);
void		free_commands(t_command **commands_dir);
void		sig_handler(int signum);
void		exit_program(int code);

#endif
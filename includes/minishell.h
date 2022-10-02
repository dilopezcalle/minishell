/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:57 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/02 16:03:46 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>

# include "structs.h"
# include "libft.h"
# include "utils.h"

static int	check_and_execute_line(char *line, char **envp);

void		rl_replace_line(const char *text, int clear_undo);
int			access_parser(t_command *commands, char *envp[]);
void		executor(t_command *commands, char *envp[]);
char		**ft_copy_double_array(char *envp_main[]);
t_command	*parser(char *command_line, char **envp);
void		free_commands(t_command **commands_dir);
int			is_command_builtin(char *command);
void		sig_handler(int signum);
void		exit_program(int code);
void		rl_clear_history(void);
char		*get_line(void);

#endif
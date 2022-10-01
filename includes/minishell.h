/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:31:57 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 12:01:13 by almirand         ###   ########.fr       */
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

char		**ft_copy_double_array(char *envp_main[]);
char		*get_line(void);
t_command	*parser(char *command_line, char	**envp);
int			access_parser(t_command *commands, char *envp[]);
int			cd_builtin(t_simple_command *command);
void		rl_replace_line(const char *text, int clear_undo);
void		executor(t_command *commands, char *envp[]);
void		free_commands(t_command **commands_dir);
void		sig_handler(int signum);
void		rl_clear_history(void);
void		exit_program(int code);

#endif

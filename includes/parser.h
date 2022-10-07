/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:14:10 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/07 10:26:30 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>

static int	create_and_append_simple_command(t_command	*commands, \
											t_token *ar_token, char ***command_args);
static int	create_simple_command(t_simple_command **command_info, \
								t_token *ar_token, char **command_arg, int index);

int			check_access_outfile(t_simple_command *command, char *file_name);
int			check_access_infile(t_simple_command *command, char *file_name);
t_token		*lexer(char *command_line, char **envp);
void		free_double_array(void **array);

#endif
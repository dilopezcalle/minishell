/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:14:10 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/13 10:33:31 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>

static int	create_and_append_simple_command(t_command	*commands, \
											char ***command_args);
static int	create_simple_command(t_simple_command **command_info, \
									char **command_arg, int index);

char		**lexer(char *command_line);
void		free_double_array(void **array);
void		check_access_outfile(t_simple_command *command, char *file_name);
void		check_access_infile(t_simple_command *command, char *file_name);

#endif
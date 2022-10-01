/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:14:10 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/01 16:22:32 by dilopez-         ###   ########.fr       */
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

char		**lexer(char *command_line, char	**envp);
void		free_double_array(void **array);
int			check_access_outfile(t_simple_command *command, char *file_name);
int			check_access_infile(t_simple_command *command, char *file_name);

#endif
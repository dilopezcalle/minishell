/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:14:10 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/04 10:11:37 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"
# include "libft.h"

# include <stdio.h>
# include <stdlib.h>

static int	create_and_append_simple_command(t_command	*commands, \
											char ***command_args_dir);
static int	create_simple_command(t_simple_command **command_info, \
									char **command_arg, int index);
static void	fill_simple_command(t_simple_command *command, char **command_arg, \
								int index, int len);
static void	print_commands(t_command **commands_dir);

char		**lexer(char *command_line);

#endif
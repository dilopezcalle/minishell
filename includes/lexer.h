/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:09:56 by dilopez-          #+#    #+#             */
/*   Updated: 2022/08/24 08:41:19 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

static char	*check_quotation_marks_and_symbols(char *command_line);
static char	*put_spaces_around_char(char *command_line, int index, char symbol);
static int	check_end_command(char ***command_args, char **separate_line, int i, int start);
static int	append_command_array(char ***command_args, char **separate_line, int start, int end);

#endif
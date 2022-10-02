/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:09:56 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/02 09:56:24 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

static int	mix_args_command(char ***command_args, char **separate, int i);
static int	check_end_command(char **separate, int i, int *start);
static int	append_command_array(char ***command_args, char **separate, \
								int start, int end);

int			check_syntax_errors(char **separate);
char		**tokens(char *line, char	**envp);
void		free_double_array(void **array);

#endif
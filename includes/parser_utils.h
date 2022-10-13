/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:15:53 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/13 16:18:25 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "structs.h"

void		redirect(char *line, char ***token, int *i, int *j);
void		init_tokenize(int *i, int *j, int	*start, int	*quote);
int			tokenize_quote(int	*start, int	*quote, char c, int i);
t_command	*malloc_commands(t_token **ar_token, char **command_args);
void		create_first_argument(t_simple_command *command, char *arg);

#endif
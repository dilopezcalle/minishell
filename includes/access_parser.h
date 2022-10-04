/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:42:26 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/04 09:35:45 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCESS_PARSER_H
# define ACCESS_PARSER_H

# include "structs.h"
# include "libft.h"

static char	*ft_get_commands_path(char *command, char **paths);
static char	**ft_get_paths(char *envp[]);

int			is_command_builtin(char *command);
void		free_double_array(void **array);

#endif
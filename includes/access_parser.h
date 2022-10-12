/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:42:26 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 17:01:45 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCESS_PARSER_H
# define ACCESS_PARSER_H

# include "structs.h"

int	access_parser(t_command *commands, char *envp[]);

#endif
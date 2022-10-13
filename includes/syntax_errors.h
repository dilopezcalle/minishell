/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:52:30 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/13 14:32:24 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ERRORS_H
# define SYNTAX_ERRORS_H

#include "structs.h"

int	check_syntax_errors(char **separate, t_token *ar_token);
int	print_syntax_error(char *str);

#endif
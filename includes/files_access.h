/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_access.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:53:27 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 17:15:10 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_ACCESS_H
# define FILES_ACCESS_H

# include "structs.h"

int	check_access_outfile(t_simple_command *command, char *file_name);
int	check_access_infile(t_simple_command *command, char *file_name);

#endif
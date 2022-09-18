/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_access.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:53:27 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/18 16:01:59 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_ACCESS_H
# define FILES_ACCESS_H

# include "structs.h"
# include "libft.h"

# include <readline/readline.h>
# include <fcntl.h>

# include <readline/readline.h>
# include <readline/history.h>

static char	*readline_infile(char *end_word);

void	rl_replace_line(const char *text, int clear_undo);
void	sig_handler(int signum);

#endif
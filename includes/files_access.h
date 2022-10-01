/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_access.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:53:27 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/27 07:59:38 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_ACCESS_H
# define FILES_ACCESS_H

# include "structs.h"
# include "libft.h"

# include <readline/readline.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

static void	dub_stdin_infile(t_simple_command *command, char *join);
static char	*readline_infile(char *end_word);
static int	fork_error_infile(void);

void		rl_replace_line(const char *text, int clear_undo);
int			join_home_folder(char **str_dir);
void		sig_handler(int signum);

#endif
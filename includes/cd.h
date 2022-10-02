/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:58:09 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/02 12:54:26 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include <stdlib.h>
# include <string.h>
# include <errno.h>

# include "structs.h"
# include "libft.h"

static int	cd_without_argument(t_simple_command *command, char **envp);

char		*ft_getenv(char	*var, char	**envp);
int			join_home_folder(char **str_dir);

#endif
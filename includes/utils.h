/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:49:00 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 18:45:54 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structs.h"

int		join_home_folder(char **str_dir, char **envp);
char	**ft_copy_double_array(char **envp_main);
void	free_commands(t_command **commands_dir);
int		is_command_builtin(char *command);
void	free_double_array(void **array);

#endif
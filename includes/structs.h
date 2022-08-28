/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:48:56 by dilopez-          #+#    #+#             */
/*   Updated: 2022/08/28 10:12:25 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_simple_command
{
	int					number_arguments;
	int					redirection_outfile;
	int					redirection_infile;
	char				**arguments;
	char				*outfile;
	char				*infile;
	char				*path;
}	t_simple_command;

typedef struct s_command
{
	int					number_simple_commands;
	t_simple_command	**simple_commands;
}	t_command;

#endif
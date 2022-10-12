/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 07:48:56 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 13:05:52 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	char				*str;
	int					*quote;
	int					len;
}						t_token;

typedef struct s_simple_command
{
	int					number_arguments;
	int					redirection_outfile;
	int					redirection_infile;
	char				**arguments;
	int					outfile;
	int					infile;
	char				*path;
}						t_simple_command;

typedef struct s_command
{
	int					number_simple_commands;
	t_simple_command	**simple_commands;
}						t_command;

typedef struct s_clean
{
	int		i;
	char	*new_token;
	int		start;
	int		quote;
	int		size;
	int		index;
	t_token	s_token;
}			t_clean;

int						g_exit_status;

#endif

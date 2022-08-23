/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:16:19 by dilopez-          #+#    #+#             */
/*   Updated: 2022/08/18 10:23:09 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "structs.h"

char	**lexer(char *command_line);

char	**ft_split(char const *s, char c);

t_command	*parser(char *command_line)
{
	//t_command	*commands;
	char		**str;

	str = lexer(command_line);
	return (0);
}

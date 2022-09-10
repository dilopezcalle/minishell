/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:14:32 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/10 14:58:46 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "libft.h"

t_command	*parser(char *command_line);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			access_parser(t_command *commands, char *envp[]);
void		print_commands(t_command **commands_dir);

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*commands;
	char		*str;

	argc = 0;
	argv = 0;
	str = ft_substr("infile < ls -l", 0, 200);
	commands = parser(str);
	if (access_parser(commands, envp))
		return (1);
	//executor(commands, envp);
	print_commands(&commands);
	return (0);
}

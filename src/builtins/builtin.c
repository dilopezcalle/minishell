/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 07:57:04 by dilopez-          #+#    #+#             */
/*   Updated: 2022/09/23 09:05:07 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "structs.h"

int	builtin_echo(t_simple_command *command);

int	execute_builtin(t_simple_command *command)
{
	if (ft_strncmp(command->arguments[0], "echo", 5) == 0)
		builtin_echo(command);
	else
		exit (0);
	return (0);
}
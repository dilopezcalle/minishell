/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:20:55 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/14 19:10:58 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_parent.h"
#include "libft.h"
#include "unset.h"
#include "export.h"
#include "cd.h"

int	execute_parent_builtin(t_simple_command *command, char **envp[])
{
	if (ft_strncmp(command->arguments[0], "cd", 3) == 0)
		return (cd_builtin(command, envp));
	if (ft_strncmp(command->arguments[0], "unset", 6) == 0)
		return (unset_builtin(command->arguments, envp));
	if (ft_strncmp(command->arguments[0], "export", 7) == 0)
		return (export_builtin(command->arguments, envp));
	return (0);
}

void	error_invalid_id(char *c)
{
	printf("concha_diminuta: export: `%s': not a valid identifier\n", c);
	g_exit_status = 1;
	return ;
}

int	ft_str_isalnum(char	*str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

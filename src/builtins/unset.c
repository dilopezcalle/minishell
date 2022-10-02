/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:36:08 by almirand          #+#    #+#             */
/*   Updated: 2022/10/01 18:09:41 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"

void	free_double_array(void **array);

int	ft_arraylen(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	unset_builtin(t_simple_command *cmd, char	***envp)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	new_envp = (char **) malloc(ft_arraylen(*envp));
	while (*envp[i])
	{
		if (ft_strncmp(*envp[i], cmd->arguments[1], ft_strlen(cmd->arguments[1])) != 0)
			new_envp[j++] = ft_strdup(*envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	free_double_array((void **)*envp);
	*envp = new_envp;
	g_exit_status = 0;
	return (0);
}

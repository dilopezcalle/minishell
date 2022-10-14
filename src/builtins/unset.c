/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:36:08 by almirand          #+#    #+#             */
/*   Updated: 2022/10/14 12:46:11 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "structs.h"
#include "libft.h"
#include "utils.h"

int	ft_arraylen(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	unset_builtin(char *var, char ***envp)
{
	int		i;
	int		j;
	char	**new_envp;
	char	*var2;

	i = 0;
	j = 0;
	g_exit_status = 0;
	if (!var)
		return (0);
	new_envp = (char **) malloc((ft_arraylen(*envp) + 1) * sizeof(char *));
	var2 = ft_strjoin(var, "=");
	while ((*envp)[i])
	{
		if ((ft_strncmp((*envp)[i], var2, ft_strlen(var2)) != 0) && \
				(ft_strncmp((*envp)[i], var, ft_strlen(var)) != 0))
			new_envp[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[j] = NULL;
	free_double_array((void **)*envp);
	*envp = new_envp;
	free(var2);
	return (0);
}

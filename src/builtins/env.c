/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:29:45 by almirand          #+#    #+#             */
/*   Updated: 2022/10/14 10:16:20 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

void	env_builtin(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=') != NULL)
			printf("%s\n", envp[i]);
		i++;
	}
	g_exit_status = 0;
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:29:45 by almirand          #+#    #+#             */
/*   Updated: 2022/10/12 17:47:28 by dilopez-         ###   ########.fr       */
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
		printf("%s\n", envp[i++]);
	g_exit_status = 0;
	exit(0);
}

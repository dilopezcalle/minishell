/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:41:13 by almirand          #+#    #+#             */
/*   Updated: 2022/10/01 17:33:08 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char	*var, char	**envp)
{
	int		i;
	int		j;
	char	*var2;

	i = 0;
	j = 0;
	var2 = ft_strjoin(var, "=");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var2, ft_strlen(var)) == 0)
		{
			while (envp[i][j] != '=' && envp[i][j])
				j++;
			return (ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - ft_strlen(var2)));
		}
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:41:13 by almirand          #+#    #+#             */
/*   Updated: 2022/10/01 16:18:15 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char	*var, char	**envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_strlcat(var, "=", ft_strlen(var));
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			while (envp[i][j] != '=' && envp[i][j])
				j++;
			return (ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - ft_strlen(var)));
		}
		i++;
	}
	return (NULL);
}
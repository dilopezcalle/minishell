/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:35:57 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/05 16:17:13 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char	*var, char	**envp)
{
	int		i;
	int		j;
	char	*var2;
	char	*str;

	i = 0;
	j = 0;
	var2 = ft_strjoin(var, "=");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var2, ft_strlen(var2)) == 0)
		{
			while (envp[i][j] != '=' && envp[i][j])
				j++;
			str = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - ft_strlen(var2));
			free(var2);
			return (str);
		}
		i++;
	}
	return (NULL);
}

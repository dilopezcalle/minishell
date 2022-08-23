/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:14:32 by dilopez-          #+#    #+#             */
/*   Updated: 2022/08/23 11:44:09 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "libft.h"

t_command	*parser(char *command_line);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

int	main(void)
{
	char	*str;

	str = ft_substr("  ls -l -a < file1 |  grep me  ", 0, 40);
	parser(str);
	return (0);
}
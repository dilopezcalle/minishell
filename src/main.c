/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 08:14:32 by dilopez-          #+#    #+#             */
/*   Updated: 2022/10/12 17:29:20 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(__attribute__((unused))int argc, __attribute__((unused))char *argv[], \
		char *envp[])
{
	minishell(envp);
	return (0);
}

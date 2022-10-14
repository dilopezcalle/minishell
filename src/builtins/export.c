/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dilopez- <dilopez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:57:45 by almirand          #+#    #+#             */
/*   Updated: 2022/10/14 19:05:37 by dilopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "structs.h"
#include "export.h"
#include "unset.h"
#include "libft.h"
#include "utils.h"

static void	export_create(char	*var, char	***envp)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	if (ft_isdigit(var[0]) || !ft_str_isalnum(var))
		return (error_invalid_id(var));
	new_envp = (char **) malloc((ft_arraylen(*envp) + 2) * sizeof(char *));
	while ((*envp)[i])
	{
		new_envp[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[j++] = ft_strdup(var);
	new_envp[j] = NULL;
	free_double_array((void **)*envp);
	*envp = new_envp;
}

static char	*export_varname(char	*var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (ft_substr(var, 0, i + 1));
		i++;
	}
	return (NULL);
}

static int	check_replace(char	*var, char	***envp)
{
	int		i;
	char	*var_name;

	i = 0;
	if (export_varname(var) != NULL)
		var_name = export_varname(var);
	else
		var_name = ft_strdup(var);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var_name, ft_strlen(var_name)) == 0)
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(var);
			free(var_name);
			return (1);
		}
		i++;
	}
	free(var_name);
	return (0);
}

int	export_builtin1(char *var, char ***envp)
{
	int		exists;

	if (var[0] == '=')
	{
		g_exit_status = 1;
		printf("export: '%s': not a valid identifier\n", var);
		return (1);
	}
	exists = check_replace(var, envp);
	if (exists == 0)
		export_create(var, envp);
	return (0);
}

int	export_builtin(char	**commands, char	***envp)
{
	int	i;

	i = 1;
	if (!commands[1])
	{
		i = 0;
		while ((*envp)[i])
			printf("declare -x %s\n", (*envp)[i++]);
		return (1);
	}
	while (commands[i])
	{
		export_builtin1(commands[i++], envp);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almirand <almirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:57:45 by almirand          #+#    #+#             */
/*   Updated: 2022/10/03 18:54:30 by almirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_arraylen(char	**envp);
void	free_double_array(void **array);
void	env_builtin(char	**envp);

int	export_print(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("declare -x %s\n", envp[i++]);
	g_exit_status = 0;
	return (0);
}

void	export_create(char	*var, char	***envp)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	new_envp = (char **) malloc((ft_arraylen(*envp) + 2) * sizeof(char *));
	while ((*envp)[i])
	{
		new_envp[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[j++] = ft_strdup(var);
	new_envp[j] = NULL;
	free_double_array((void **)*envp);
	envp = &new_envp;
}

char	*export_varname(char	*var)
{
	int		i;
	char	*varname;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (ft_substr(var, 0, i + 1));
		i++;
	}
	return (NULL);
}

int	check_replace(char	*var, char	***envp)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = export_varname(var);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], var_name, ft_strlen(var_name) != 0))
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(var);
			return (1);
		}
		i++;
	}
	free(var_name);
	return (0);
}

int	export_builtin(char	*var, char	***envp)
{
	int		exists;

	g_exit_status = 0;
	if (!var)
		return (export_print(*envp));
	if (var[0] == '=')
	{
		g_exit_status = 1;
		printf("export: '%s': not a valid identifier", var);
		return (1);
	}
	exists = check_replace(var, envp);
	if (exists == 0) //crear nuevo envp con la variable si no existe
		export_create(var, envp);
	env_builtin(*envp);
	return (0);
}

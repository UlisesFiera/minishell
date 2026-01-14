/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:54:16 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/30 16:57:42 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_env_var(char **environ, char *var_name)
{
	int	i;
	int	name_len;

	if (!var_name)
		return (-1);
	i = 0;
	name_len = 0;
	while (var_name[name_len] && var_name[name_len] != '=')
		name_len++;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, name_len) == 0
			&& environ[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	find_env_var_2(char **environ, char *var_name)
{
	int	i;
	int	name_len;

	if (!var_name)
		return (-1);
	i = 0;
	name_len = 0;
	while (var_name[name_len] && var_name[name_len] != '=')
		name_len++;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, name_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	**dup_env_with_size(char **env, int count)
{
	int		i;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_env(new_env);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	return (new_env);
}

char	**add_env_var(char **env, char *new_var)
{
	int		count;
	char	**new_env;

	count = 0;
	while (env[count])
		count++;
	new_env = dup_env_with_size(env, count);
	if (!new_env)
		return (NULL);
	new_env[count] = ft_strdup(new_var);
	if (!new_env[count])
	{
		free_env(new_env);
		free(new_env);
		return (NULL);
	}
	new_env[count + 1] = NULL;
	free_env(env);
	free(env);
	return (new_env);
}

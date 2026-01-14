/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:40:38 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/30 14:41:05 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var(char **env, char *var)
{
	int	i;
	int	equal;

	i = 0;
	while (env[i])
	{
		equal = 0;
		while (env[i][equal] != '\0' && env[i][equal] != '=')
			equal++;
		if (ft_strncmp(env[i], var, equal) == 0 && var[equal] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

char	**unset_mem(char **env, char *var, int *total_elements, int *index)
{
	char	**new_env;

	*total_elements = 0;
	while (env[*total_elements])
		*total_elements = *total_elements + 1;
	*index = find_var(env, var);
	if (*index == -1)
		return (env);
	new_env = (char **)malloc(sizeof(char *) * (*total_elements));
	return (new_env);
}

char	**unset_handler(char **env, char *var)
{
	int		total_elements;
	int		index;
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = unset_mem(env, var, &total_elements, &index);
	if (new_env == env)
		return (env);
	while (j < total_elements)
	{
		if (j == index)
		{
			j++;
			continue ;
		}
		new_env[i++] = ft_strdup(env[j++]);
	}
	new_env[i] = NULL;
	free_env(env);
	free(env);
	return (new_env);
}

int	unset(t_gen_data *data, char **commands)
{
	int	i;

	i = 1;
	data->last_exit_status = 0;
	if (!commands[i])
		return (0);
	while (commands[i])
	{
		data->exec_env = unset_handler(data->exec_env, commands[i]);
		data->exec_env_export = \
		unset_handler(data->exec_env_export, commands[i]);
		i++;
	}
	return (0);
}

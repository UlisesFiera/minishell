/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:40:23 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/30 23:48:15 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**update_env_handler(char **new_env, char **old_env, int size, int flag)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size)
	{
		if (j == flag)
		{
			j++;
			continue ;
		}
		new_env[i] = ft_strdup(old_env[j]);
		if (!new_env[i])
		{
			free_env(new_env);
			free(new_env);
			return (NULL);
		}
		i++;
		j++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**update_env(char **old_env, int size, int flag)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (NULL);
	while (i < size)
	{
		new_env[i] = NULL;
		i++;
	}
	new_env = update_env_handler(new_env, old_env, size, flag);
	free_env(old_env);
	free(old_env);
	return (new_env);
}

static void	export_handle_arg(t_gen_data *data, char *arg, int *valid,
		int *invalid)
{
	if (ft_strchr(arg, '='))
	{
		if (!check_valid_var_name(arg))
		{
			export_var_env(data, arg);
			export_var_exp1(data, arg);
			*valid = 1;
		}
		else
			*invalid = 1;
	}
	else
	{
		if (!check_valid_var_name(arg))
		{
			export_var_exp2(data, arg);
			*valid = 1;
		}
		else
			*invalid = 1;
	}
}

int	export(t_gen_data *data, char **executables, char **exec_env)
{
	int	i;
	int	valid;
	int	invalid;

	i = 1;
	if (!executables[i])
	{
		sort_export(data->exec_env_export);
		export_empty_args(data, exec_env);
		return (data->last_exit_status);
	}
	valid = 0;
	invalid = 0;
	while (executables[i])
	{
		export_handle_arg(data, executables[i], &valid, &invalid);
		i++;
	}
	drop_duplicated(data);
	export_exit_status(data, valid, invalid);
	return (data->last_exit_status);
}

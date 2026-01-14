/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+  	+#+           */
/*   Created: 2025/07/27 20:09:01 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/27 20:09:01 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_var_env(t_gen_data *data, char *var)
{
	int		index;
	char	**new_env;

	index = find_env_var(data->exec_env, var);
	new_env = NULL;
	if (index >= 0)
	{
		free(data->exec_env[index]);
		data->exec_env[index] = ft_strdup(var);
	}
	else
	{
		new_env = add_env_var(data->exec_env, var);
		if (new_env)
			data->exec_env = new_env;
	}
}

void	export_var_exp1(t_gen_data *data, char *var)
{
	int		index;
	char	**new_env;

	index = find_env_var(data->exec_env_export, var);
	if (index >= 0)
	{
		if (has_equal(var))
		{
			free(data->exec_env_export[index]);
			data->exec_env_export[index] = ft_strdup(var);
		}
	}
	else
	{
		new_env = add_env_var(data->exec_env_export, var);
		if (new_env)
			data->exec_env_export = new_env;
	}
}

void	export_var_exp2(t_gen_data *data, char *var)
{
	int		index;
	char	**new_env;

	index = find_env_var_2(data->exec_env_export, var);
	if (index >= 0)
	{
		if (has_equal(var))
		{
			free(data->exec_env_export[index]);
			data->exec_env_export[index] = ft_strdup(var);
		}
	}
	else
	{
		new_env = add_env_var(data->exec_env_export, var);
		if (new_env)
			data->exec_env_export = new_env;
	}
}

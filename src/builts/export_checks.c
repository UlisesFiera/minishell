/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/07/27 20:21:07 by ulfernan          #+#    #+#             */
/*   Updated: 2025/07/27 20:21:07 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_exit_status(t_gen_data *data, int valid, int invalid)
{
	if (invalid == 1 && valid == 0)
		data->last_exit_status = 1;
	else if (invalid == 1 && valid == 1)
		data->last_exit_status = 1;
	else
		data->last_exit_status = 0;
}

void	export_empty_args(t_gen_data *data, char **exec_env)
{
	int	i;

	i = 0;
	data->last_exit_status = 0;
	while (exec_env[i])
	{
		print_export(exec_env[i]);
		i++;
	}
}

int	has_equal(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	are_duplicated(t_gen_data *data, int i, int j)
{
	int	len_i;
	int	len_j;

	len_i = 0;
	len_j = 0;
	while (data->exec_env_export[i][len_i] != '\0'
		&& data->exec_env_export[i][len_i] != '=')
		len_i++;
	while (data->exec_env_export[j][len_j] != '\0'
		&& data->exec_env_export[j][len_j] != '=')
		len_j++;
	if (len_i == len_j && ft_strncmp(data->exec_env_export[i],
			data->exec_env_export[j], len_i) == 0)
	{
		if (has_equal(data->exec_env_export[i]))
			return (j);
		else
			return (i);
	}
	return (0);
}

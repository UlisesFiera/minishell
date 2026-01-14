/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:05:02 by asalguer          #+#    #+#             */
/*   Updated: 2025/07/29 17:41:31 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	drop_duplicated_handler(t_gen_data *data, int *i, int *size)
{
	int	j;
	int	flag;

	while (*i < *size)
	{
		j = 0;
		flag = 0;
		while (j < *size)
		{
			if (j != *i)
			{
				flag = are_duplicated(data, *i, j);
				if (flag != 0)
				{
					data->exec_env_export = update_env(data->exec_env_export,
							*size, flag);
					(*size)--;
					break ;
				}
			}
			j++;
		}
		(*i)++;
	}
}

void	drop_duplicated(t_gen_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (data->exec_env_export[size] != NULL)
		size++;
	drop_duplicated_handler(data, &i, &size);
}

void	print_export(char *env_var)
{
	int	i;

	i = 0;
	write(1, "declare -x ", 11);
	if (has_equal(env_var) == 1)
	{
		while (env_var[i] != '\0')
		{
			if (i > 0 && env_var[i - 1] == '=')
				write(1, "\"", 1);
			write(1, &env_var[i], 1);
			i++;
		}
		write(1, "\"", 1);
	}
	else
	{
		while (env_var[i] != '\0')
		{
			write(1, &env_var[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}

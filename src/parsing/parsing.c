/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulfernan <ulfernan@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:40:35 by ulfernan          #+#    #+#             */
/*   Updated: 2025/05/09 13:40:35 by ulfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_var_count(t_gen_data *data, char **env)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (data->executables[i])
	{
		if (data->quotes[i] == 1)
			parse_env_vars_quotes(data, env, data->executables[i], i);
		else if (data->quotes[i] != 2)
		{
			j = 0;
			while(data->executables[i][j])
			{
				if (data->executables[i][j] == '$')
					count++;
				j++;
			}
		}
		i++;
	}
	return (count);
}

void	env_var_check(t_gen_data *data, char **env)
{
	int		count;
	char	**env_paths;

	count = env_var_count(data, env);
	if (count == 0)
		return ;
	env_paths = malloc(sizeof(char *) * (count + 1));
	env_paths[count] = NULL;
	replace_env(data, env_paths, env);
}

void	null_exec_cleaner(t_gen_data *data)
{
	char	**clean_array;
	int		size;
	int		i;

	clean_array = NULL;
	size = 0;
	i = 0;
	while (data->executables[i])
	{
		if (data->executables[i][0] != '\0')
			size++;
		i++;
	}
	clean_array = malloc(sizeof(char *) * size + 1);
	clean_array[size] = NULL;
	i = 0;
	size = 0;
	while (data->executables[i])
	{
		if (data->executables[i][0] != '\0')
			clean_array[size++] = data->executables[i];
		i++;
	}
	data->executables = clean_array;
}

void	parse_input(t_gen_data *data, char **env)
{
	int		exec_count;
	int		index;
	int		i;

	exec_count = exec_counter(data->input);
	data->executables = malloc(sizeof(char *) * (exec_count + 1));
	if (!data->executables)
		return ;
	data->executables[exec_count] = NULL;
	init_quotes(data, exec_count);
	index = 0;
	i = 0;
	while (i < exec_count)
	{
		data->executables[i] = exec_split(data->input, &index, i, data);
		i++;
	}
	null_exec_cleaner(data);
	env_var_check(data, env);
	set_pipe_flag(data);
}

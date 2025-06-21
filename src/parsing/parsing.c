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
		//printf("entering %s index %i\n", data->executables[i], i);
		if (data->quotes[i] == 1)
			parse_env_vars_quotes(data, env, data->executables[i], i);
		else if (data->quotes[i] != 2)
		{
			j = 0;
			while (data->executables[i][j])
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
	free(env_paths);
}

/*void	null_exec_cleaner(t_gen_data *data)
{
	int		size;
	int		i;

	data->clean_array = NULL;
	size = 0;
	i = 0;
	while (data->executables[i])
	{
		if (data->executables[i][0] != '\0')
			size++;
		i++;
	}
	data->clean_array = malloc(sizeof(char *) * (size + 1));
	data->updated_quotes = malloc(sizeof(int) * size);
	data->clean_array[size] = NULL;
	i = 0;
	size = 0;
	while (data->executables[i])
	{
		if (data->executables[i][0] != '\0')
		{
			data->clean_array[size] = data->executables[i];
			data->updated_quotes[size] = data->quotes[i];
			size++;
		}
		else
			free(data->executables[i]);
		i++;
	}
	free(data->quotes);
	free(data->executables);
	data->executables = data->clean_array;
	data->quotes = data->updated_quotes;
} */

void	reposition_arrays(t_gen_data *data, int *exec_count, int i)
{
	int	j;

	j = i + 1;
	while (data->executables[j])
	{
		free(data->executables[j]);
		data->executables[j] = data->executables[j + 1];
		j++;
	}
	(*exec_count)--;
	j = i + 1;
	while (j < *exec_count)
	{
		data->cat_quotes[j] = data->cat_quotes[j + 1];
		j++;
	}
}

void	cat_executables(t_gen_data *data, int exec_count)
{
	int		i;
	char	*cat_command;

	i = 0;
	while (i < exec_count)
	{
		if (data->cat_quotes[i] == 1)
		{
			cat_command = ft_strjoin(
					data->executables[i], data->executables[i + 1]);
			free(data->executables[i]);
			data->executables[i] = ft_strdup(cat_command);
			free(cat_command);
			reposition_arrays(data, &exec_count, i);
		}
		i++;
	}
}

void	parse_input(t_gen_data *data, char **env)
{
	int		exec_count;
	int		index;
	int		i;

	exec_count = exec_counter(data->input);
	data->exec_count = exec_count;
	data->executables = malloc(sizeof(char *) * (exec_count + 1));
	if (!data->executables)
		return ;
	data->executables[exec_count] = NULL;
	init_quotes(data, exec_count);
	index = 0;
	i = 0;
	while (i < exec_count)
	{
		data->executables[i] = exec_split(&index, i, data);
		i++;
	}
	//null_exec_cleaner(data);
	env_var_check(data, env);
	set_pipe_flag(data);
	cat_executables(data, exec_count);
}

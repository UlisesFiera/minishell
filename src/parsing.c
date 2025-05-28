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

#include "minishell.h"

char	*get_env_var(char *command, int index)
{
	char	*env_var;
	int		i;
	int		j;
	int		size;

	size = 0;
	i = index + 1;
	while (command[i] && command[i] >= 'A' && command[i] <= 'Z')
	{
		size++;
		i++;
	}
	env_var = malloc(sizeof(char) * (size + 1));
	env_var[size] = '\0';
	i = index + 1;
	j = 0;
	while (command[i] && command[i] >= 'A' && command[i] <= 'Z')
	{
		env_var[j] = command[i];
		i++;
		j++;
	}
	return (env_var);
}

char	*env_cleaner(char *executable, char **env, t_gen_data *data) // must free
{
	char	*name;
	char	*path;
	char	*sufix;
	char	*final_env;
	int		i;
	int		j;
	int		index;
	int		exit_status;

	if (*executable == '?')
	{
		exit_status = WIFEXITED(data->exit_status);
		final_env = ft_itoa(exit_status);
		return (final_env);
	}
	i = 0;
	while (executable[i] && executable[i] >= 'A' && executable[i] <= 'Z')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (executable[i] && executable[i] >= 'A' && executable[i] <= 'Z')
	{
		name[i] = executable[i];
		i++;
	}
	name[i] = '\0';
	path = ft_getenv(name, env);
	if (!path)
		return (NULL);
	j = 0;
	index = i;
	while (executable[i])
	{
		i++;
		j++;
	}
	i = 0;
	sufix = malloc(sizeof(char) * (j + 1));
	while (executable[index])
	{
		sufix[i] = executable[index];
		index++;
		i++;
	}
	sufix[i] = '\0';
	final_env = ft_strjoin(path, sufix);
	return (final_env);
}

void	parse_env_vars_quotes(t_gen_data *data, char **env, char *command, int index)
{
	int		count;
	int		i;
	int		j;
	char	**env_paths;
	char	*new_string;

	count = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '$')
			count++;
		i++;
	}
	if (count == 0)
		return ;
	env_paths = malloc(sizeof(char *) * (count + 1));
	env_paths[count] = NULL;
	i = 0;
	j = 0;
	while (command[i])
	{
		if (command[i] == '$')
		{
			env_paths[j] = env_cleaner(command + i + 1, env, data);
			if (!env_paths[j])
			{
				free(env_paths);
				return ;
			}
			new_string = ft_strinsert(command, env_paths[j], i);
			command = new_string;
			j++;
		}
		i++;
	}
	free(data->executables[index]);
	data->executables[index] = command;
}

void	parse_env_vars(t_gen_data *data, char **env) // must free env paths
{
	int		count;
	int		i;
	int		j;
	char	**env_paths;

	count = 0;
	i = 0;
	while (data->executables[i])
	{
		if (data->quotes[i] == 1)
			parse_env_vars_quotes(data, env, data->executables[i], i);
		else if (data->executables[i][0] == '$' && data->quotes[i] != 2)
			count++;
		i++;
	}
	if (count == 0)
		return ;
	env_paths = malloc(sizeof(char *) * (count + 1));
	env_paths[count] = NULL;
	i = 0;
	j = 0;
	while (data->executables[i])
	{
		if (data->executables[i][0] == '$')
		{
			env_paths[j] = env_cleaner(data->executables[i] + 1, env, data);
			if (!env_paths[j])
			{
				free(env_paths);
				return ;
			}
			free(data->executables[i]);
			data->executables[i] = env_paths[j];
			j++;
		}
		i++;
	}
}

void	set_pipe_flag(t_gen_data *data)
{
	int	i;

	i = 0;
	while (data->executables[i])
	{
		if (!strcmp(data->executables[i], "|"))
			data->pipe_flag++;
		i++;
	}
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
	parse_env_vars(data, env);
	set_pipe_flag(data);
}
